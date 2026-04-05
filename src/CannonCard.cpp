/**
 * @file CannonCard.cpp
 * @brief Implements the CannonCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "CannonCard.hpp"
#include "CardSelector.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

CannonCard::CannonCard(int val) : Card(CardType::Cannon, val) {}

std::string CannonCard::str() const {
    return "Cannon(" + std::to_string(value()) + ")";
}

void CannonCard::play(Game& game, Player& player) {
    static_cast<void>(player);
    auto& other = game.otherPlayer();
    auto& otherBank = other.bank();
    if(otherBank.empty()) {
        std::cout
            << "Cannon: No cards to discard from the other player's bank.\n";
        return;
    }

    Card* const toDiscard = CardSelector::selectAndRemove(
        otherBank,
        "Cannon: Which suit to discard from " + other.name() + "'s bank?");

    game.discardCard(toDiscard);
    std::cout << "Discarded " << toDiscard->str() << " from " << other.name()
              << "'s bank." << '\n';
}
