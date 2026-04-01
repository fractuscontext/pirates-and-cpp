/**
 * @file AnchorCard.cpp
 * @brief Implements the AnchorCard ability.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "AnchorCard.hpp"
#include "Player.hpp"
#include <algorithm>
#include <iostream>

AnchorCard::AnchorCard(int val) : Card(CardType::Anchor, val) {}

std::string AnchorCard::str() const {
    return "Anchor (" + std::to_string(value()) + ")";
}

void AnchorCard::play(Game& game, Player& player) {
    static_cast<void>(game);
    auto& playArea = player.playArea();
    const auto turn = std::ranges::find(playArea, this);
    if(turn != playArea.end()) {
        std::cout
            << "Anchor: Any cards drawn before this are safe and moved to "
               "the bank."
            << '\n';
        auto& mutableBank = player.bank();

        for(auto cardIt = playArea.begin(); cardIt != turn; ++cardIt) {
            std::cout << "Saving " << (*cardIt)->str() << " to bank." << '\n';
            mutableBank.push_back(*cardIt);
        }
        playArea.erase(playArea.begin(), turn);
    }
}
