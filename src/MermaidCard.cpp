/**
 * @file MermaidCard.cpp
 * @brief Implements the MermaidCard; no ability, higher point values (4–9).
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "MermaidCard.hpp"
#include <iostream>

MermaidCard::MermaidCard(int val) : Card(CardType::Mermaid, val) {}

std::string MermaidCard::str() const {
    return "Mermaid (" + std::to_string(value()) + ")";
}

void MermaidCard::play(Game& game, Player& player) {
    static_cast<void>(game);
    static_cast<void>(player);
    std::cout << "No effect but Mermaids are worth more.\n";
}
