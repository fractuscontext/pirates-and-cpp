/**
 * @file RandomProvider.cpp
 * @brief Implements DefaultRandomProvider with hardware-seeded RNG.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "RandomProvider.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <random>

void DefaultRandomProvider::shuffle(CardCollection& cards) {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::shuffle(cards.begin(), cards.end(), gen);
}

std::string DefaultRandomProvider::pickPlayerName() {
    std::array<std::string, 10> const names
        = {"Sam", "Billy", "Jen",   "Bob",  "Sally",
           "Joe", "Sue",   "Sasha", "Tina", "Marge"};
    return names.at(
        rand()
        % 10); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index,cert-msc30-c,cert-msc50-cpp)
}
