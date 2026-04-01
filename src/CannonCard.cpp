/**
 * @file CannonCard.cpp
 * @brief Implements the CannonCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "CannonCard.hpp"
#include "Game.hpp"
#include "InputHelper.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

CannonCard::CannonCard(int val) : Card(CardType::Cannon, val) {}

std::string CannonCard::str() const {
    return "Cannon (" + std::to_string(_value) + ")";
}

void CannonCard::play(Game& game, Player& player) {
    static_cast<void>(player);
    auto& other = game.otherPlayer();
    const auto& otherBank = other.bank();
    if(otherBank.empty()) {
        std::cout << "Cannon: No cards to discard from the other player's bank."
                  << '\n';
        return;
    }

    std::map<CardType, Card*> topCards;
    for(auto* card : otherBank) {
        if(!topCards.contains(card->type())
           || card->value() > topCards[card->type()]->value()) {
            topCards[card->type()] = card;
        }
    }

    std::cout << "Cannon: Which suit to discard from " << other.name()
              << "'s bank?" << '\n';
    std::vector<CardType> availableTypes;
    int i = 0;
    for(auto const& [type, card] : topCards) {
        availableTypes.push_back(type);
        std::cout << i++ << ": " << card->str() << '\n';
    }

    int const choice
        = InputHelper::askChoice("Choice: ", availableTypes.size());

    CardType const chosenType = availableTypes[choice];
    Card* const toDiscard = topCards[chosenType];

    auto& mutableBank = other.bank();
    const auto turn = std::ranges::find(mutableBank, toDiscard);
    if(turn != mutableBank.end()) {
        mutableBank.erase(turn);
        game.discardCard(toDiscard);
        std::cout << "Discarded " << toDiscard->str() << " from "
                  << other.name() << "'s bank." << '\n';
    }
}
