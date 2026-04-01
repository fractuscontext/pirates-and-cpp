/**
 * @file HookCard.cpp
 * @brief Implements the HookCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "HookCard.hpp"
#include "Game.hpp"
#include "InputHelper.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

HookCard::HookCard(int val) : Card(CardType::Hook, val) {}

std::string HookCard::str() const {
    return "Hook (" + std::to_string(_value) + ")";
}

void HookCard::play(Game& game, Player& player) {
    const auto& bank = player.bank();
    if(bank.empty()) {
        std::cout << "No cards in your Bank. Play continues.\n";
        return;
    }

    std::map<CardType, Card*> topCards;
    for(auto* card : bank) {
        if(!topCards.contains(card->type())
           || card->value() > topCards[card->type()]->value()) {
            topCards[card->type()] = card;
        }
    }

    std::cout << "Hook: Which suit to play from your bank?" << '\n';
    std::vector<CardType> availableTypes;
    int i = 0;
    for(auto const& [type, card] : topCards) {
        availableTypes.push_back(type);
        std::cout << i++ << ": " << card->str() << '\n';
    }

    int const choice
        = InputHelper::askChoice("Choice: ", availableTypes.size());

    CardType const chosenType = availableTypes[choice];
    Card* const toPlay = topCards[chosenType];

    auto& mutableBank = player.bank();
    const auto it = std::ranges::find(mutableBank, toPlay);
    if(it != mutableBank.end()) {
        mutableBank.erase(it);
        std::cout << "Playing " << toPlay->str() << " from bank!" << '\n';
        bool const bust = player.playCard(toPlay, game);
        if(bust) {
            std::cout << "Hook play caused a BUST!" << '\n';
        }
    }
}
