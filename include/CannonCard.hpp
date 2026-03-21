/**
 * @file CannonCard.hpp
 * @brief Declares the CannonCard class for the Cannon suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef CANNON_CARD_HPP
#define CANNON_CARD_HPP

#include "Card.hpp"
#include <string>

/**
 * @brief Represents a Cannon card.
 *
 * When played, the player selects a suit and the highest-value card of that
 * suit is discarded from the opponent's bank to the discard pile.
 */
class CannonCard : public Card {
public:
    /**
     * @brief Constructs a CannonCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit CannonCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Cannon(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Prompts the player to choose a suit and discards the top card of that suit from the opponent's bank.
     *
     * If the opponent's bank is empty, a message is printed and the ability is skipped.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
