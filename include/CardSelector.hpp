/**
 * @file CardSelector.hpp
 * @brief Reusable UI helper for selecting one card (by suit) from a bank.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef CARD_SELECTOR_HPP
#define CARD_SELECTOR_HPP

#include "Card.hpp"
#include <string>

/**
 * @brief Presents a numbered list of the highest-value card per suit in a
 *        bank, prompts the user to pick one, and removes the chosen card.
 *
 * Used by Cannon (discard from opponent), Sword (steal from opponent),
 * and Hook (pull from own bank).
 */
namespace CardSelector {

/**
 * @brief Prompts the user to pick a card from a bank and removes it.
 *
 * Builds a per-suit "top card" map, displays it as a numbered menu,
 * asks for a choice, erases the chosen card from the bank, and
 * returns a pointer to it.
 *
 * @param bank   Mutable reference to the bank to select from.
 * @param prompt The header text shown before the numbered list
 *               (e.g. "Cannon: Which suit to discard from Bob's bank?").
 * @return Pointer to the card removed from the bank.
 */
Card* selectAndRemove(CardCollection& bank, const std::string& prompt);

} // namespace CardSelector

#endif
