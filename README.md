<!--
SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>

SPDX-License-Identifier: MIT
-->

# Dead Man's Draw++

A C++20 terminal implementation of the card game [Dead Man's Draw](https://www.mayday-games.com/products/dead-mans-draw), playable by two players in a command-line interface.

## About

Dead Man's Draw is a press-your-luck card game. Players take turns drawing cards from the deck and adding them to the current stack. Each card suit has a unique special ability that triggers when drawn. A player may bank their current stack at any time to keep its points — but if they draw a card matching a suit already in the stack, they **bust**, losing everything in the stack for that turn.

### Card Suits & Abilities

| Suit    | Ability |
|---------|---------|
| Cannon  | Discards the top card of a chosen suit from the opponent's bank. |
| Chest   | No immediate effect; grants bonus draws when banked together with a Key. |
| Key     | No immediate effect; activates the Chest bonus when banked together with a Chest. |
| Sword   | Steals the top card of a chosen suit from the opponent's bank. |
| Hook    | Returns the top card of a chosen suit from the player's own bank to the stack. |
| Oracle  | Reveals the top card of the deck before the player decides to draw again. |
| Map     | Draws three cards from the discard pile; the player must play one. |
| Mermaid | No ability; higher point values (4–9) compared to other suits. |
| Kraken  | Forces the player to draw and play three consecutive cards. |
| Anchor  | Cards drawn before this are saved to the bank even on a bust. |

## Building

### Prerequisites

- CMake 3.20+
- A C++20-capable compiler (GCC, Clang, or MSVC)
- [Ninja](https://ninja-build.org/) (optional, used by `build.sh`)

### Linux / macOS

```bash
chmod +x build.sh
./build.sh
```

The compiled binary is placed at `build/DeadMansDrawPlusPlus`.

### Windows (Visual Studio 2022)

```bat
build.bat
```

This generates a Visual Studio 2022 solution in `vs_build/`.

### Manual CMake

```bash
cmake -B build -S .
cmake --build build
./build/DeadMansDrawPlusPlus
```

## Project Structure

The project follows the [Pitchfork](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs) layout convention.

```
include/   — Public header files (.hpp)
src/       — Implementation files (.cpp)
docs/      — Project documentation and Doxygen output
tests/     — Test placeholder
```

## Documentation

API documentation is generated with [Doxygen](https://www.doxygen.nl/). Pre-built HTML docs are available in `docs/doxygen_output/html/`.

To regenerate:

```bash
doxygen Doxyfile
```

## License

This project is licensed under the [MIT License](LICENSES/MIT.txt).

© 2026 Claire Tam — REUSE compliant.
