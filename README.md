<!--
SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>

SPDX-License-Identifier: MIT
-->

# Dead Man's Draw++

COMP 1039 — Design Patterns with C++ — Assignment 1

A two-player, press-your-luck card game implemented as a C++20 console
application. Players take turns drawing cards from a shared 60-card deck.
Each card belongs to one of 10 pirate-themed suits, and every suit has a
unique ability that fires when drawn. Push your luck to amass treasure — but
draw a duplicate suit and you **bust**, losing your entire haul for the turn.

## Game Rules

- **Deck**: 60 cards across 10 suits, each with 6 cards at varying point
  values.
- **Turns**: On each turn a player draws cards one at a time into their
  Play Area. They may stop at any point to **bank** those cards permanently.
- **Bust**: Drawing a card whose suit already appears in the Play Area
  discards everything to the shared Discard Pile.
- **Scoring**: At game end, each player's score is the sum of the
  **highest-value card per suit** in their Bank.
- **Game end**: The deck is empty or 20 total turns have been played.
  Highest score wins.

### Card Suits and Abilities

| Suit | Ability | Values |
| --------- | --------- | -------- |
| Cannon | Discard the top card of any suit from the opponent's Bank. | 2–7 |
| Chest | No immediate effect. If banked with a Key, draw bonus cards from the Discard Pile. | 2–7 |
| Key | See Chest above. | 2–7 |
| Sword | Steal the top card of any suit from the opponent's Bank into your Play Area. | 2–7 |
| Hook | Play the top card of any suit from your own Bank into your Play Area. | 2–7 |
| Oracle | Peek at the next card in the Deck before deciding to draw. | 2–7 |
| Map | Draw up to 3 cards from the Discard Pile; you must play one. | 2–7 |
| Mermaid | No ability, but higher point values. | 4–9 |
| Kraken | Must draw and play 3 additional cards consecutively. | 2–7 |
| Anchor | All cards drawn before the Anchor are saved to the Bank, even on a bust. | 2–7 |

## Design Overview

The system follows an object-oriented design with loose coupling between
the `Game` driver and individual card behaviours:

- **Game** (singleton) — Owns the deck, discard pile, and two players.
  Controls the turn loop, drawing, busting, and end-of-game scoring.
- **Player** — Manages a Play Area and a Bank. Detects busts via a
  dedicated `BustChecker`. Delegates card-specific behaviour through
  virtual dispatch on `Card`.
- **Card** (abstract) — Base class with `play()` (ability on draw) and
  `willAddToBank()` (ability on banking). Ten concrete subclasses
  (`CannonCard`, `ChestCard`, `KeyCard`, `SwordCard`, `HookCard`,
  `OracleCard`, `MapCard`, `MermaidCard`, `KrakenCard`, `AnchorCard`)
  each implement their own ability.

### Key Design Decisions

- **Card abilities are self-contained.** Each subclass overrides `play()`
  to execute its effect, keeping `Game` and `Card` loosely coupled.
  Adding or removing a suit requires no changes to `Game` or `Player`.
- **Chest/Key combo uses `willAddToBank()`.** The bonus-draw logic lives
  in `ChestCard::willAddToBank()`, called by `Player::bankPlayArea()`
  just before each card enters the Bank — matching the rubric's
  recommended virtual hook.
- **Anchor behaviour stays in `AnchorCard`.** The Anchor saves pre-Anchor
  cards to the Bank from within its own `play()` override and updates
  `BustChecker` accordingly, with no special-case code in `Game`.
- **Singleton Game.** Only one `Game` instance exists at a time
  (Meyer's singleton), as required.
- **Dynamic allocation with manual cleanup.** All `Card` and `Player`
  objects are heap-allocated via `new`. Destructors in `Player` and
  `Game::cleanup()` free all owned pointers.
- **`BustChecker` for O(1) bust detection.** A `std::set<CardType>` tracks
  suits in the Play Area, avoiding a linear scan on every draw.
- **`RandomProvider` abstraction.** Shuffling and name generation are
  injected via a virtual interface, enabling deterministic testing
  with `NoShuffleProvider`.

## Building

### Prerequisites

- CMake 3.20 or later
- A C++20-capable compiler (GCC 11+, Clang 14+, or MSVC 19.30+)
- Ninja (optional, used by `build.sh`)

### Linux and macOS

```bash
./build.sh            # build and run the game (AddressSanitizer enabled)
./build.sh test       # build and run all unit tests
./build.sh coverage   # generate an HTML coverage report
```

### Windows (Visual Studio 2022)

```bat
build.bat
```

This generates a Visual Studio 2022 solution in `vs_build/` and builds a
Release executable.

### Manual CMake

```bash
cmake -B build -S .
cmake --build build
./build/DeadMansDrawPlusPlus
```

## Project Structure

```text
include/   Header files (.hpp) — one per class
src/       Implementation files (.cpp)
tests/     Unit tests (Google Test)
docs/      Doxygen output and contributing guide
```

## Testing

107 unit tests across five suites, using
[Google Test](https://github.com/google/googletest)
(fetched automatically by CMake at configure time):

| Suite | Scope |
| ------- | ------- |
| `CardTest` | Card type, value, and string representation for all 10 suits. |
| `PlayerTest` | Play area, banking, bust detection, scoring, Chest/Key combo. |
| `GameTest` | Deck composition, shuffling, turns, rounds, discard pile. |
| `AbilityTest` | Each card ability in isolation, including edge cases. |
| `LifecycleTest` | End-to-end game turns with scripted decks and input. |

```bash
./build.sh test
```

Or manually:

```bash
cmake -B build -S .
cmake --build build
cd build && ctest --output-on-failure
```

## Documentation

API documentation is generated with [Doxygen](https://www.doxygen.nl/).
Pre-built HTML docs are in `docs/doxygen_output/html/`.

To regenerate:

```bash
doxygen Doxyfile
```

## Contributing

This project is structured to transition into a standalone open-source game after the assignment. Coding standards, commit conventions, and tooling are documented in [docs/CONTRIBUTING.md](docs/CONTRIBUTING.md).

## License

This project is licensed under the [MIT License](LICENSES/MIT.txt).
REUSE-compliant — see [REUSE.toml](REUSE.toml) for attribution.
