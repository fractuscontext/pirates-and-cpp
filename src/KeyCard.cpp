#include <iostream>
/**
 * @file KeyCard.cpp
 * @brief Implements the KeyCard; ability fires at banking time via Player::bankPlayArea().
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "KeyCard.hpp"

KeyCard::KeyCard(int val) : Card(CardType::Key, val) {}

std::string KeyCard::str() const {
    return "Key (" + std::to_string(_value) + ")";
}

void KeyCard::play(Game& game, Player& player) {
    static_cast<void>(game);
    static_cast<void>(player);
    std::cout
        << "No immediate effect. If banked with a chest,\ndraw as many bonus "
           "cards from the Discard pile as you moved into your Bank.\n";
}
