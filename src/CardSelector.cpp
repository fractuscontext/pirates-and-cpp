/**
 * @file CardSelector.cpp
 * @brief Implements the shared card selection UI for Cannon, Sword, and Hook.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "CardSelector.hpp"
#include "InputHelper.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

namespace CardSelector {

Card* selectAndRemove(CardCollection& bank, const std::string& prompt) {
    std::map<CardType, Card*> topCards;
    for(auto* card : bank) {
        if(!topCards.contains(card->type())
           || card->value() > topCards[card->type()]->value()) {
            topCards[card->type()] = card;
        }
    }

    std::cout << prompt << '\n';
    std::vector<CardType> availableTypes;
    int idx = 1;
    for(auto const& [type, card] : topCards) {
        availableTypes.push_back(type);
        std::cout << "  " << idx++ << ": " << card->str() << '\n';
    }
    std::cout << '\n';

    int const choice
        = InputHelper::askChoice("Choice: ", availableTypes.size());

    CardType const chosenType = availableTypes[choice];
    Card* const chosen = topCards[chosenType];

    const auto iter = std::ranges::find(bank, chosen);
    if(iter != bank.end()) {
        bank.erase(iter);
    }

    return chosen;
}

} // namespace CardSelector
