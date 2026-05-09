#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.10"
# dependencies = [
#   "pyspellchecker>=0.8",
#   "pyahocorasick>=2",
# ]
# ///
"""
Scan autocorrect_dict.txt for false-trigger risk: a typo is "risky" if it
appears as a substring inside a real English or German word, because the
autocorrect engine fires mid-word by default. Anchored typos like ':foo:'
are checked against whole-word matches instead.

Run:  ./check_autocorrect.py    (uv handles deps)
"""

import sys
from collections import defaultdict
from pathlib import Path

import ahocorasick
from spellchecker import SpellChecker

DICT_FILE = Path(__file__).parent / "autocorrect_dict.txt"
TOP_N = 50_000  # consider only the N most frequent words per language


def parse_dict(path: Path) -> list[str]:
    typos = []
    for raw in path.read_text().splitlines():
        line = raw.split("#", 1)[0].strip()
        if "->" not in line:
            continue
        typo, _, _ = line.partition("->")
        typos.append(typo.strip().lower())
    return typos


def normalize(typo: str) -> tuple[str, bool, bool]:
    return typo.strip(":"), typo.startswith(":"), typo.endswith(":")


def common_words(spell: SpellChecker, top_n: int) -> set[str]:
    items = sorted(spell.word_frequency.dictionary.items(), key=lambda kv: -kv[1])
    return {w for w, _ in items[:top_n]}


def scan(label: str, words: set[str], typos: list[str]) -> dict[str, list[str]]:
    """Aho-Corasick scan: build automaton from un-anchored typos, run each
    word through it, collect any hits. Anchored ':foo:' typos are checked
    separately as whole-word membership."""
    unanchored: dict[str, str] = {}  # inner → original typo string
    anchored: dict[str, str] = {}
    for typo in typos:
        inner, anc_l, anc_r = normalize(typo)
        if len(inner) < 3 or not inner.replace("'", "").isalpha():
            continue
        if anc_l and anc_r:
            anchored[inner] = typo
        else:
            unanchored[inner] = typo

    flagged: dict[str, list[str]] = defaultdict(list)
    if unanchored:
        A = ahocorasick.Automaton()
        for inner in unanchored:
            A.add_word(inner, inner)
        A.make_automaton()
        for w in words:
            if w in unanchored:
                continue  # typo IS the word, not "inside" another word
            for _end_idx, inner in A.iter(w):
                if len(flagged[unanchored[inner]]) < 6:
                    flagged[unanchored[inner]].append(w)
    for inner, typo in anchored.items():
        if inner in words:
            flagged[typo] = [inner]

    print(f"\n=== {label} (top {len(words):,} words) ===")
    if not flagged:
        print("  ✓ no false-trigger candidates")
    else:
        for t, hits in sorted(flagged.items()):
            print(f"  {t:18} ⚠ in: {', '.join(sorted(hits))}")
    return dict(flagged)


def main() -> int:
    typos = parse_dict(DICT_FILE)
    print(f"Loaded {len(typos)} typos from {DICT_FILE.name}")

    # internal substring check (mirrors what qmk generate does)
    print("\n=== internal substring check ===")
    inner_pairs = []
    for i, a in enumerate(typos):
        ia = a.strip(":")
        for b in typos[i + 1 :]:
            ib = b.strip(":")
            if ia == ib:
                continue
            if ia in ib or ib in ia:
                short, long_ = (a, b) if len(ia) < len(ib) else (b, a)
                inner_pairs.append((short, long_))
    if not inner_pairs:
        print("  ✓ no internal substring conflicts")
    else:
        for s, l in inner_pairs:
            print(f"  ⚠ {s} ⊂ {l}")

    en = SpellChecker(language="en")
    de = SpellChecker(language="de")
    en_words = common_words(en, TOP_N)
    de_words = common_words(de, TOP_N)

    en_flagged = scan("English", en_words, typos)
    de_flagged = scan("German", de_words, typos)

    total = len(en_flagged) + len(de_flagged) + len(inner_pairs)
    print(f"\nSummary: {total} risky entries")
    return 1 if total else 0


if __name__ == "__main__":
    sys.exit(main())
