# bytemouse / Corne

Personal QMK keymap for the [Corne](https://github.com/foostan/crkbd) (a 42-key split ortholinear), tuned for German typing and home-row mods.

## Layers

| | Layer | Purpose |
|---|---|---|
| 0 | `QWERTY` | Standard US QWERTY (default) |
| 1 | `KOY` | German Neo-style optimized layout with home-row mods |
| 2 | `LOWER` | Numbers, navigation, media, copy/paste |
| 3 | `RAISE` | Programming symbols (German layout) |
| 4 | `ADJUST` | F-keys, default-layer toggle, Caps Word |

`LOWER` and `RAISE` are reached by holding the corresponding thumb key. `ADJUST` is reached by `Enter` (hold) on the left thumb or via `LOWER + ADJUST` chord.

## Features

- **Chordal Hold** — hold-tap only fires when paired with a key on the *opposite* hand, eliminating most home-row-mod misfires.
- **Flow Tap** (`150 ms`) — suppresses hold during fast typing for an even cleaner HRM experience.
- **Caps Word** (`CW_TOGG` on ADJUST) — tap to start, types one word in caps incl. German umlauts (`ä`, `ö`, `ü`, `ß`), auto-releases.
- **Home-row mods (KOY only)** — GASC pattern: `H = ⌘`, `A = ⎇`, `E = ⇧`, `I = ^`.
- **Layer-tap thumbs** — `Tab/Lower`, `BSpc/Raise`, `Enter/Adjust`, `Esc/Alt`, `Space/Shift`.
- **Ctrl shortcuts** — `^Z ^Y ^X ^C ^V` mapped on LOWER for copy/cut/paste/undo/redo (German layout).
- **OLED display** — master shows the current layer; slave shows the Corne logo.

## Tooling

| Tool | What | Output |
|---|---|---|
| [keymap-drawer](https://github.com/caksoylar/keymap-drawer) | Generates `keymap.svg` from `keymap.c` | `keymap.svg`, `keymap.yaml` |
| [keymapviz](https://github.com/yskoht/keymapviz) | Rewrites layer ASCII-art in `keymap.c` | `keymap.c` (in place) |

Both run automatically as pre-commit hooks under `githooks/`. Activate on a fresh clone with:

```sh
git config core.hooksPath keyboards/crkbd/keymaps/bytemouse/githooks
```

## Future ideas

QMK features worth adding later, in rough order of payoff:

1. [**Repeat Key**](https://docs.qmk.fm/features/repeat_key) — re-emits the last key, great for doubled letters and arrow nav on KOY where common pairs span hands.
2. [**Combos**](https://docs.qmk.fm/features/combo) — chord two keys → one keycode (e.g. `J K → Esc`); reclaims keys without changing layout.
3. [**Autocorrect**](https://docs.qmk.fm/features/autocorrect) — tiny on-keyboard typo dictionary that silently fixes common slips.
4. [**Layer Lock**](https://docs.qmk.fm/features/layer_lock) — pin a momentary layer "on" without holding the activator, useful for sustained symbol entry.
5. [**Tri-Layer**](https://docs.qmk.fm/features/tri_layer) — built-in helper for the `LOWER + RAISE → ADJUST` pattern this keymap already uses; pure cleanup.
6. [**Mouse Keys**](https://docs.qmk.fm/features/mouse_keys) — keyboard-driven cursor and scroll, niche unless skipping the trackpad matters.
7. [**Speculative Hold**](https://github.com/getreuer/qmk-modules/tree/main/speculative_hold) — emits the tap immediately and rolls back on hold, eliminating HRM latency at the cost of brief flicker; experimental.

## Size optimization (if needed)

Default-on QMK features that this keymap doesn't use, with rough flash savings if disabled:

| Setting | Where | Saves | What it disables |
|---|---|---|---|
| `MAGIC_ENABLE = no` | `rules.mk` | ~500 B | `MAGIC_*` runtime config keys (NKRO/Ctrl-GUI swap, etc.) |
| `SPACE_CADET_ENABLE = no` | `rules.mk` | ~150 B | Tap LShift → `(`, tap RShift → `)` |
| `GRAVE_ESC_ENABLE = no` | `rules.mk` | ~50 B | `KC_GESC` (Esc that becomes `` ` `` when shifted) |
| `RGB_MATRIX_ENABLE = no` | `rules.mk` | ~varies | Per-key RGB scheduler (separate from RGBLIGHT) |
| `#define NO_ACTION_ONESHOT` | `config.h` | ~100 B | One-shot key state machine |
| `#define LAYER_STATE_8BIT` | `config.h` | ~50 B | Reduces layer state from 32-bit to 8-bit (fine, you have 5 layers) |
| `#undef LOCKING_SUPPORT_ENABLE`<br>`#undef LOCKING_RESYNC_ENABLE` | `config.h` | small | Cherry MX Lock switch support |

**Don't disable** `EXTRAKEY_ENABLE` (kills volume/media keys) or `LTO_ENABLE` (single biggest saver).

## Build

```sh
qmk compile -kb crkbd/rev1 -km bytemouse
```

Current firmware size: **~17.8 KB / 28 KB** on Pro Micro AVR.
