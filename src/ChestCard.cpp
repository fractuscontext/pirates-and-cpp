/**
 * @file ChestCard.cpp
 * @brief Implements the ChestCard; ability fires at banking time via Player::bankPlayArea().
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "ChestCard.hpp"
#include "Game.hpp"
#include "Player.hpp"
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

void ChestCard::willAddToBank(Game& game, Player& player) {
    bool hasKey = false;
    for(auto* card : player.playArea()) {
        if(card->type() == CardType::Key) {
            hasKey = true;
            break;
        }
    }
    if(!hasKey) {
        return;
    }

    int const bonusCount = static_cast<int>(player.playArea().size());
    std::cout << "\nChest and Key combination! Drawing " << bonusCount
              << " bonus cards from discard.\n";
    for(int i = 0; i < bonusCount && !game.discardPile().empty(); ++i) {
        Card* const bonus = game.discardPile().back();
        game.discardPile().pop_back();
        player.bank().push_back(bonus);
        std::cout << "  Added " << bonus->str() << " to bank.\n";
    }
    std::cout << '\n';
}
