/**
 * @file MapCard.hpp
 * @brief Declares the MapCard class for the Map suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef MAP_CARD_HPP
#define MAP_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Map card.
 *
 * When played, up to three cards are drawn from the discard pile and presented
 * to the player, who must choose one to add to their play area. The remaining
 * cards are returned to the discard pile. If the discard pile is empty, the
 * ability is skipped.
 */
class MapCard : public Card {
public:
    /**
     * @brief Constructs a MapCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit MapCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Map(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Draws up to three cards from the discard pile and prompts the player to play one.
     *
     * The chosen card is played into the play area; its ability triggers and a bust may result.
     * Unchosen cards are returned to the discard pile.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
