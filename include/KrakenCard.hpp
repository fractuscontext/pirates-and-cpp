/**
 * @file KrakenCard.hpp
 * @brief Declares the KrakenCard class for the Kraken suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef KRAKEN_CARD_HPP
#define KRAKEN_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Kraken card.
 *
 * When played, the player is forced to draw and play three additional cards
 * consecutively from the deck. Drawing stops early if the deck runs out or
 * the player busts.
 */
class KrakenCard : public Card {
public:
    /**
     * @brief Constructs a KrakenCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit KrakenCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Kraken(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Forces the player to draw and play three consecutive cards from the deck.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
