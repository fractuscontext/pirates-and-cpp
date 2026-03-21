/**
 * @file MapCard.cpp
 * @brief Implements the MapCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "MapCard.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

MapCard::MapCard(int val) : Card(CardType::Map, val) {}

std::string MapCard::str() const {
    return "Map (" + std::to_string(_value) + ")";
}

void MapCard::play(Game& game, Player& player) {
    auto& discard = game.discardPile();
    if(discard.empty()) {
        std::cout << "Map: No cards in the discard pile to draw." << '\n';
        return;
    }

    std::cout << "Map: Choose a card from the discard pile to play:" << '\n';
    int const drawCount = std::min(3, static_cast<int>(discard.size()));
    std::vector<Card*> options;
    for(int i = 0; i < drawCount; ++i) {
        options.push_back(discard.back());
        discard.pop_back();
        std::cout << i << ": " << options.back()->str() << '\n';
    }

    int choice = 0;
    std::cout << "Choice: ";
    if(!(std::cin >> choice) || choice < 0
       || std::cmp_greater_equal(choice, options.size())) {
        std::cout << "Invalid choice. Skipping Map ability. Cards returned to "
                     "discard."
                  << '\n';
        for(auto* card : options) {
            discard.push_back(card);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    Card* const chosen = options[choice];
    std::cout << "Playing " << chosen->str() << " from discard!" << '\n';

    for(int i = 0; std::cmp_less(i, options.size()); ++i) {
        if(i != choice) {
            discard.push_back(options[i]);
        }
    }

    bool const bust = player.playCard(chosen, game);
    if(bust) {
        std::cout << "Map play caused a BUST!" << '\n';
    }
}
