#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.10"
# dependencies = ["pyspellchecker>=0.8", "pyahocorasick>=2"]
# ///
"""
Expand autocorrect_dict.txt with empirically-common typos from:
  * codespell programmer dictionary (Python/Java/general)
  * Wikipedia English common misspellings (A-Z subpages)

Pipeline per candidate:
  1. Reject if typo not pure a-z lowercase, or <5 chars.
  2. Reject if correction is not ASCII (umlauts/Unicode would break send_string).
  3. Reject if the correction is ambiguous (codespell entries with "X, disabled"
     or multiple corrections).
  4. Reject if typo equals the correction.
  5. Substring filter: drop the candidate if its typo is a substring of, or
     contains, any existing or already-accepted typo.
  6. False-trigger filter: if the typo appears as a substring inside a common
     English or German word (top 50K), wrap it in ':typo:' to require word
     boundaries.

The result is appended to autocorrect_dict.txt under a new section, then the
QMK header is regenerated and the firmware is recompiled. Run as:
    ./expand_autocorrect.py [--max 200] [--dry-run]
"""

import argparse
import re
import subprocess
import sys
import urllib.request
from pathlib import Path

import ahocorasick
from spellchecker import SpellChecker

HERE = Path(__file__).parent
DICT_FILE = HERE / "autocorrect_dict.txt"
QMK_ROOT = HERE.parents[3]  # …/qmk_firmware — qmk CLI subcommands depend on cwd
KEYBOARD = "crkbd/rev1"
KEYMAP = "bytemouse"
MARKER = "# ---------- expand_autocorrect.py: bulk additions ----------"

CORPUS_TSV = HERE / "corpus_eng_typos.tsv"
# Pre-extracted from the GitHub Typo Corpus v1.0.0 (see ./extract_corpus.py
# or scripts in /tmp/parse_corpus.py + /tmp/filter_corpus.py). Format:
#   count<TAB>typo<TAB>correction
# Sorted by count desc. Already filtered: typo not a real EN word, ASCII
# only, length ≥5, Damerau-Levenshtein ≤2 from correction.

UA = {"User-Agent": "qmk-autocorrect-helper/1.0"}


def http_get(url: str) -> str:
    req = urllib.request.Request(url, headers=UA)
    with urllib.request.urlopen(req, timeout=30) as r:
        return r.read().decode("utf-8", errors="replace")


def parse_corpus(path: Path) -> list[tuple[str, str, int]]:
    """Read the GitHub Typo Corpus TSV. Returns (typo, correction, count)
    tuples already sorted by count desc."""
    pairs = []
    for line in path.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        parts = line.split("\t")
        if len(parts) != 3:
            continue
        n, typo, corr = parts
        try:
            count = int(n)
        except ValueError:
            continue
        pairs.append((typo.lower(), corr, count))
    return pairs


def parse_existing(path: Path) -> set[str]:
    typos = set()
    for raw in path.read_text().splitlines():
        if raw.strip() == MARKER:
            break  # everything below this is auto-generated, ignore for "existing"
        line = raw.split("#", 1)[0].strip()
        if "->" not in line:
            continue
        typo, _, _ = line.partition("->")
        typos.add(typo.strip().lower().strip(":"))
    return typos


def truncate_at_marker(path: Path) -> None:
    lines = path.read_text().splitlines()
    for i, line in enumerate(lines):
        if line.strip() == MARKER:
            # drop the marker line and any preceding blank/comment lines we added
            while i > 0 and lines[i - 1].strip() == "":
                i -= 1
            path.write_text("\n".join(lines[:i]) + "\n")
            return


def is_typo_valid(t: str) -> bool:
    return len(t) >= 5 and t.isalpha() and t.isascii() and t.islower()


def is_corr_valid(c: str) -> bool:
    if not (c and c.isascii() and not any(ch.isspace() for ch in c)):
        return False
    # Drop any correction with uppercase letters: title-case (Bitcoin,
    # Dockerfile, February, Additional) and ALL-CAPS (UNKNOWN, VIOLATION).
    # Auto-section corrections must be all-lowercase — capitalisation is
    # context-dependent and shouldn't be imposed mid-sentence. Manual
    # sections handle intentional capitals (German nouns: Adresse, Beispiel).
    if c != c.lower():
        return False
    return True


def all_substrings(s: str, min_len: int = 1) -> set[str]:
    return {s[i:j] for i in range(len(s)) for j in range(i + min_len, len(s) + 1)}


def common_words(spell: SpellChecker, top_n: int) -> set[str]:
    items = sorted(spell.word_frequency.dictionary.items(), key=lambda kv: -kv[1])
    return {w for w, _ in items[:top_n]}


def find_risky(typo_set: set[str], words: set[str]) -> set[str]:
    """Return typos that appear as a strict substring inside any common word.
    Uses Aho-Corasick: O(|patterns| + |texts| + #matches) total."""
    if not typo_set:
        return set()
    A = ahocorasick.Automaton()
    for t in typo_set:
        A.add_word(t, t)
    A.make_automaton()
    risky: set[str] = set()
    for w in words:
        if w in typo_set:
            continue  # the typo IS this word; not a false-trigger inside another
        for _end_idx, t in A.iter(w):
            risky.add(t)
    return risky


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--max", type=int, default=300, help="cap on new entries")
    ap.add_argument("--dry-run", action="store_true", help="don't write/compile")
    args = ap.parse_args()

    print(f"→ reading GitHub Typo Corpus TSV: {CORPUS_TSV.name} ...", flush=True)
    corpus_pairs = parse_corpus(CORPUS_TSV)
    print(f"   {len(corpus_pairs)} pre-filtered pairs (sorted by frequency)")

    existing = parse_existing(DICT_FILE)
    print(f"→ existing dict: {len(existing)} typos\n")

    # Single auto source: GitHub Typo Corpus (real frequency-ranked typos
    # from 200K commits). German entries are hand-curated above the marker.
    seen_typo: set[str] = set()
    # Track corpus count so we can sort by it later. List of (typo, corr, count).
    candidates: list[tuple[str, str, int]] = []
    for typo, corr, count in corpus_pairs:
        if typo in seen_typo or typo in existing:
            continue
        if not is_typo_valid(typo):
            continue
        if not is_corr_valid(corr):
            continue
        if typo == corr.lower():
            continue
        seen_typo.add(typo)
        candidates.append((typo, corr, count))
    print(f"→ {len(candidates)} candidates passed shape filters")

    # Rank candidates by raw typo frequency from the corpus — this is direct
    # ground truth (how often the typo actually got committed and reverted),
    # not the correction-frequency proxy we used with codespell.
    candidates.sort(key=lambda c: (-c[2], len(c[0]), c[0]))

    # Substring filter (greedy in frequency order: high-frequency wins).
    accepted_typos: set[str] = set(existing)
    accepted_subs: set[str] = set()
    for t in existing:
        accepted_subs |= all_substrings(t, min_len=5)
    accepted: list[tuple[str, str, int]] = []
    for typo, corr, count in candidates:
        if typo in accepted_subs:
            continue  # candidate is substring of some accepted typo
        if all_substrings(typo, min_len=5) & accepted_typos:
            continue  # some accepted typo is substring of candidate
        accepted_typos.add(typo)
        accepted_subs |= all_substrings(typo, min_len=5)
        accepted.append((typo, corr, count))
    print(f"→ {len(accepted)} survived substring filter (kept high-freq on conflict)")

    # Cap.
    if args.max and len(accepted) > args.max:
        accepted = accepted[: args.max]
        print(f"→ capped to {args.max}")

    # Real-word + false-trigger filter:
    #   * Drop candidates whose typo IS a real EN or DE word — anchoring with
    #     :typo: would still false-correct the user's legitimate typing of
    #     that word (e.g. German "arges", "belog").
    #   * Anchor surviving candidates whose typo is a strict substring of
    #     a common word (still safe under word-boundary rules).
    print("→ loading wordlists for false-trigger check...", flush=True)
    en = SpellChecker(language="en")
    de = SpellChecker(language="de")
    en_words = common_words(en, 50_000)
    de_words = common_words(de, 50_000)
    real_words = en_words | de_words
    before = len(accepted)
    accepted = [(t, c, n) for t, c, n in accepted if t not in real_words]
    print(f"→ {before - len(accepted)} dropped (typo IS a real EN/DE word)")
    accepted_typo_set = {t for t, _, _ in accepted}
    risky = find_risky(accepted_typo_set, en_words)
    risky |= find_risky(accepted_typo_set, de_words)
    final = [(f":{t}:" if t in risky else t, c, n) for t, c, n in accepted]
    print(f"→ {len(risky)} entries anchored as :typo: for word-boundary safety")

    # Defensive: assert no duplicate typo (compared by inner content, ignoring
    # ':' anchors) within `final` or against `existing`. Raises on conflict so
    # we never silently emit duplicate rules.
    inner_counts: dict[str, int] = {}
    for t, _c, _n in final:
        key = t.strip(":")
        inner_counts[key] = inner_counts.get(key, 0) + 1
    dupes_within = [k for k, n in inner_counts.items() if n > 1]
    dupes_vs_existing = [t for t, _, _ in final if t.strip(":") in existing]
    if dupes_within or dupes_vs_existing:
        print(f"\n!! ABORTING: {len(dupes_within)} duplicate(s) within new block, "
              f"{len(dupes_vs_existing)} duplicate(s) vs existing dict")
        for d in dupes_within[:10]: print(f"   within: {d}")
        for d in dupes_vs_existing[:10]: print(f"   vs existing: {d}")
        return 2
    print(f"→ dedup check OK: 0 duplicates in {len(final)} new entries\n")

    # Order in dict: highest typo frequency first (from corpus count).
    # NO inline comments — QMK's autocorrect generator does NOT strip
    # end-of-line '# ...' text and would parse it as part of the correction.
    out_lines: list[str] = ["", "", MARKER]
    out_lines.append("# Auto-curated from the GitHub Typo Corpus v1.0.0.")
    out_lines.append("# Ordered top-to-bottom by real-world typo frequency")
    out_lines.append("# (commit-edit count from 200K+ open-source repositories).")
    out_lines.append("# Re-run ./expand_autocorrect.py to refresh.")
    out_lines.append("")
    for typo, corr, _n in final:
        out_lines.append(f"{typo:<24} -> {corr}")
    block = "\n".join(out_lines) + "\n"

    if args.dry_run:
        print(block)
        print(f"\n[dry-run] would add {len(final)} entries")
        return 0

    print(f"→ appending {len(final)} entries to {DICT_FILE.name}")
    truncate_at_marker(DICT_FILE)  # idempotent: drop any prior auto-section
    with DICT_FILE.open("a") as f:
        f.write(block)

    print("→ regenerating autocorrect_data.h ...", flush=True)
    r = subprocess.run(
        ["qmk", "generate-autocorrect-data", "-kb", KEYBOARD, "-km", KEYMAP, str(DICT_FILE)],
        capture_output=True, text=True, cwd=QMK_ROOT,
    )
    print(r.stdout)
    if r.returncode != 0:
        print(r.stderr, file=sys.stderr)
        return r.returncode

    print("→ compiling firmware ...", flush=True)
    r = subprocess.run(
        ["qmk", "compile", "-kb", KEYBOARD, "-km", KEYMAP],
        capture_output=True, text=True, cwd=QMK_ROOT,
    )
    tail = r.stdout.splitlines()[-15:]
    print("\n".join(tail))
    return r.returncode


if __name__ == "__main__":
    sys.exit(main())
