/**
 * @file HookCard.cpp
 * @brief Implements the HookCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "HookCard.hpp"
#include "CardSelector.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

HookCard::HookCard(int val) : Card(CardType::Hook, val) {}

std::string HookCard::str() const {
    return "Hook(" + std::to_string(value()) + ")";
}

void HookCard::play(Game& game, Player& player) {
    auto& bank = player.bank();
    if(bank.empty()) {
        std::cout << "No cards in your Bank. Play continues.\n";
        return;
    }

    Card* const toPlay = CardSelector::selectAndRemove(
        bank, "Hook: Which suit to play from your bank?");

    std::cout << "Playing " << toPlay->str() << " from bank!" << '\n';
    bool const bust = player.playCard(toPlay, game);
    if(bust) {
        std::cout << "Hook play caused a BUST!" << '\n';
    }
}
