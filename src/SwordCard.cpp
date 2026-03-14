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
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <utility>
#include <vector>

SwordCard::SwordCard(int val) : Card(CardType::Sword, val) {}

std::string SwordCard::str() const {
    return "Sword (" + std::to_string(_value) + ")";
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
    int i = 0;
    for(auto const& [type, card] : topCards) {
        availableTypes.push_back(type);
        std::cout << i++ << ": " << card->str() << '\n';
    }

    int choice = 0;
    std::cout << "Choice: ";
    if(!(std::cin >> choice) || choice < 0
       || std::cmp_greater_equal(choice, availableTypes.size())) {
        std::cout << "Invalid choice. Skipping Sword ability." << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    CardType const chosenType = availableTypes[choice];
    Card* const toSteal = topCards[chosenType];

    auto& mutableOtherBank = other.bank();
    const auto it = std::ranges::find(mutableOtherBank, toSteal);
    if(it != mutableOtherBank.end()) {
        mutableOtherBank.erase(it);
        std::cout << "Stole " << toSteal->str() << " from " << other.name()
                  << "!" << '\n';
        bool const bust = player.playCard(toSteal, game);
        if(bust) {
            std::cout << "Steal caused a BUST!" << '\n';
        }
    }
}
