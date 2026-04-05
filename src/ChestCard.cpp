/**
 * @file ChestCard.cpp
 * @brief Implements the ChestCard; ability fires at banking time via Player::bankPlayArea().
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "ChestCard.hpp"
#include <iostream>

ChestCard::ChestCard(int val) : Card(CardType::Chest, val) {}

std::string ChestCard::str() const {
    return "Chest(" + std::to_string(value()) + ")";
}

void ChestCard::play(Game& game, Player& player) {
    static_cast<void>(game);
    static_cast<void>(player);
    std::cout
        << "No immediate effect. If banked with a Key, draw as many bonus "
           "cards from the Discard pile as you moved into your Bank.\n";
}
