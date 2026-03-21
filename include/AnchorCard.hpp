/**
 * @file AnchorCard.hpp
 * @brief Declares the AnchorCard class for the Anchor suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef ANCHOR_CARD_HPP
#define ANCHOR_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents an Anchor card.
 *
 * When played, any cards already in the play area before this Anchor are
 * immediately moved to the player's bank and are safe even if the player
 * subsequently busts.
 */
class AnchorCard : public Card {
public:
    /**
     * @brief Constructs an AnchorCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit AnchorCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Anchor(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Saves all cards drawn before this Anchor to the player's bank.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
