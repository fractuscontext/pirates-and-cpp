/**
 * @file main.cpp
 * @brief Entry point for Dead Man's Draw++.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */

#include "Game.hpp"
#include "GameTitle.hpp"
#include <iostream>

/**
 * @brief Entry point for the Dead Man's Draw++ application.
 *
 * Retrieves the singleton Game instance, initialises it, and starts the game loop.
 *
 * @return int Execution status (0 for success).
 */
int main() {
    std::cout << GAME_TITLE << "\n";
    std::cout << "Starting Dead Man's Draw++!\n";
    Game& game = Game::instance();
    game.init();
    game.start();
    return 0;
}
