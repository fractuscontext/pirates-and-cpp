/**
 * @file ChestCard.hpp
 * @brief Declares the ChestCard class for the Chest suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef CHEST_CARD_HPP
#define CHEST_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Chest card.
 *
 * Has no immediate effect when drawn. If banked alongside a Key card,
 * the player draws bonus cards from the discard pile equal to the number
 * of cards moved into the bank.
 */
class ChestCard : public Card {
public:
    /**
     * @brief Constructs a ChestCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit ChestCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Chest(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief No immediate effect when drawn.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
