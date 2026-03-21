/**
 * @file OracleCard.hpp
 * @brief Declares the OracleCard class for the Oracle suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef ORACLE_CARD_HPP
#define ORACLE_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents an Oracle card.
 *
 * When played, the player is shown the identity of the top card of the deck
 * before they decide whether to draw again, giving them informed decision-making.
 */
class OracleCard : public Card {
public:
    /**
     * @brief Constructs an OracleCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit OracleCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Oracle(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Reveals the top card of the deck to the player.
     *
     * If the deck is empty, a message is printed instead.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
