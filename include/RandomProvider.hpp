/**
 * @file RandomProvider.hpp
 * @brief Abstracts randomness so that shuffling and name selection can be
 *        mocked or seeded for deterministic testing.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef RANDOM_PROVIDER_HPP
#define RANDOM_PROVIDER_HPP

#include "Card.hpp"
#include <string>

/**
 * @brief Interface for all randomness consumed by the game.
 *
 * Implement this to supply a seeded or scripted source of randomness for
 * deterministic replays and testing.
 */
class RandomProvider {
public:
    virtual ~RandomProvider() = default;

    /**
     * @brief Shuffles a card collection in place.
     *
     * @param cards The collection to shuffle.
     */
    virtual void shuffle(CardCollection& cards) = 0;

    /**
     * @brief Returns a player name selected by this provider.
     *
     * @return A name string.
     */
    virtual std::string pickPlayerName() = 0;

    /** @brief Default constructor. */
    RandomProvider() = default;
    /** @brief Copy constructor (defaulted). */
    RandomProvider(const RandomProvider&) = default;
    /** @brief Copy assignment (defaulted). @return Reference to this. */
    RandomProvider& operator=(const RandomProvider&) = default;
    /** @brief Move constructor (defaulted). */
    RandomProvider(RandomProvider&&) = default;
    /** @brief Move assignment (defaulted). @return Reference to this. */
    RandomProvider& operator=(RandomProvider&&) = default;
};

/**
 * @brief Default provider that uses hardware entropy for shuffling and
 *        C rand() for name selection (matches original behaviour).
 */
class DefaultRandomProvider : public RandomProvider {
public:
    void shuffle(CardCollection& cards) override;
    std::string pickPlayerName() override;
};

#endif
