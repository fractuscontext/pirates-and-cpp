/**
 * @file SwordCard.cpp
 * @brief Implements the SwordCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "SwordCard.hpp"
#include "Game.hpp"
#include "InputHelper.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

SwordCard::SwordCard(int val) : Card(CardType::Sword, val) {}

std::string SwordCard::str() const {
    return "Sword (" + std::to_string(value()) + ")";
}

void SwordCard::play(Game& game, Player& player) {
    auto& other = game.otherPlayer();
    const auto& otherBank = other.bank();
    if(otherBank.empty()) {
        std::cout << "Sword: No cards to steal from the other player's bank."
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

    std::cout << "Sword: Which suit to steal from " << other.name()
              << "'s bank?" << '\n';
    std::vector<CardType> availableTypes;
    int idx = 0;
    for(auto const& [type, card] : topCards) {
        availableTypes.push_back(type);
        std::cout << idx++ << ": " << card->str() << '\n';
    }

    int const choice
        = InputHelper::askChoice("Choice: ", availableTypes.size());

    CardType const chosenType = availableTypes[choice];
    Card* const toSteal = topCards[chosenType];

    auto& mutableOtherBank = other.bank();
    const auto iter = std::ranges::find(mutableOtherBank, toSteal);
    if(iter != mutableOtherBank.end()) {
        mutableOtherBank.erase(iter);
        std::cout << "Stole " << toSteal->str() << " from " << other.name()
                  << "!" << '\n';
        bool const bust = player.playCard(toSteal, game);
        if(bust) {
            std::cout << "Steal caused a BUST!" << '\n';
        }
    }
}
