/**
 * @file BustChecker.hpp
 * @brief Single-responsibility bust detection for a card collection.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef BUST_CHECKER_HPP
#define BUST_CHECKER_HPP

#include "Card.hpp"
#include <set>

/**
 * @brief Detects duplicate-suit busts in a card collection.
 *
 * Maintains a set of seen suits so that bust detection is O(1) per card
 * instead of O(n) per check. Call wouldBust() before adding, then
 * recordCard() after adding. Call reset() when the play area is cleared.
 */
class BustChecker {
public:
    /**
     * @brief Returns true if adding a card of the given type would cause a bust.
     *
     * @param type The suit of the card about to be added.
     * @return true if a card of this suit is already in the play area.
     */
    [[nodiscard]] bool wouldBust(CardType type) const {
        return _seenSuits.contains(type);
    }

    /**
     * @brief Records a card's suit as present in the play area.
     *
     * @param type The suit of the card that was just added.
     */
    void recordCard(CardType type) { _seenSuits.insert(type); }

    /**
     * @brief Returns whether a bust has occurred (at least one duplicate suit).
     *
     * @return true if the play area has a bust.
     */
    [[nodiscard]] bool isBust() const { return _bust; }

    /**
     * @brief Marks the bust state as true.
     */
    void setBust() { _bust = true; }

    /**
     * @brief Resets all tracked state. Call when the play area is cleared.
     */
    void reset() {
        _seenSuits.clear();
        _bust = false;
    }

private:
    std::set<CardType> _seenSuits; /**<Suits currently in the play area. */
    bool _bust{false};             /**<Whether a bust has occurred. */
};

#endif
