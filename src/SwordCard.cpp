/**
 * @file SwordCard.cpp
 * @brief Implements the SwordCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "SwordCard.hpp"
#include "CardSelector.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

SwordCard::SwordCard(int val) : Card(CardType::Sword, val) {}

std::string SwordCard::str() const {
    return "Sword(" + std::to_string(value()) + ")";
}

void SwordCard::play(Game& game, Player& player) {
    auto& other = game.otherPlayer();
    auto& otherBank = other.bank();
    if(otherBank.empty()) {
        std::cout << "Sword: No cards to steal from the other player's bank.\n";
        return;
    }

    Card* const toSteal = CardSelector::selectAndRemove(
        otherBank,
        "Sword: Which suit to steal from " + other.name() + "'s bank?");

    std::cout << "Stole " << toSteal->str() << " from " << other.name() << "!"
              << '\n';
    bool const bust = player.playCard(toSteal, game);
    if(bust) {
        std::cout << "Steal caused a BUST!" << '\n';
    }
}
