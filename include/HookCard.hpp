/**
 * @file HookCard.hpp
 * @brief Declares the HookCard class for the Hook suit.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef HOOK_CARD_HPP
#define HOOK_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Hook card.
 *
 * When played, the player selects a suit and the highest-value card of that
 * suit is pulled from the player's own bank back into their play area.
 * The returned card's ability is triggered and may cause a bust.
 */
class HookCard : public Card {
public:
    /**
     * @brief Constructs a HookCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit HookCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Hook(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Prompts the player to choose a suit and returns the top card of that suit from their bank to the play area.
     *
     * If the player's bank is empty, a message is printed and the ability is skipped.
     * The returned card's ability is triggered and may cause a bust.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
