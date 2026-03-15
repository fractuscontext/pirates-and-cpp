/**
 * @file KrakenCard.cpp
 * @brief Implements the KrakenCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "KrakenCard.hpp"
#include "Game.hpp"
#include "Player.hpp"

KrakenCard::KrakenCard(int val) : Card(CardType::Kraken, val) {}

std::string KrakenCard::str() const {
    return "Kraken (" + std::to_string(_value) + ")";
}

void KrakenCard::play(Game& game, Player& player) {
    for(int i = 0; i < 3; ++i) {
        if(!game.deck().empty()) {
            game.drawCard(player);
            if(player.isBust()) {
                break;
            }
        }
    }
}
