/**
 * @file OracleCard.cpp
 * @brief Implements the OracleCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "OracleCard.hpp"
#include "Game.hpp"
#include <iostream>

OracleCard::OracleCard(int val) : Card(CardType::Oracle, val) {}

std::string OracleCard::str() const {
    return "Oracle (" + std::to_string(_value) + ")";
}

void OracleCard::play(Game& game, Player& player) {
    static_cast<void>(player);
    Card const* top = game.topDeck();
    if(top != nullptr) {
        std::cout << "Oracle: The next card in the deck is " << top->str()
                  << "." << '\n';
    } else {
        std::cout << "Oracle: No cards left in the deck." << '\n';
    }
}
