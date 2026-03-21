/**
 * @file Player.hpp
 * @brief Declares the Player class representing a player in Dead Man's Draw++.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include <map>
#include <string>
#include <vector>

class Game;

/**
 * @brief Represents a player in the game, owning a play area and a bank.
 *
 * The Player manages cards added to their current play area during a turn.
 * When the player banks, all play area cards move to the permanent bank.
 * The bank is scored at the end of the game.
 */
class Player {
public:
    /**
     * @brief Constructs a Player with the given name.
     *
     * @param name The player's display name.
     */
    explicit Player(std::string name);

    /**
     * @brief Destructor. Deletes all dynamically allocated cards in the play area and bank.
     */
    ~Player();

    /**
     * @brief Adds a card to the play area and, if no bust, triggers its ability.
     *
     * A bust occurs when a card of the same suit already exists in the play area.
     * If the player busts, the card is still added but its ability is not triggered.
     *
     * @param card Pointer to the card to play. Ownership transfers to this player.
     * @param game The current game instance, passed to the card's play() method.
     * @return true if adding the card caused a bust, false otherwise.
     */
    bool playCard(Card* card, Game& game);

    /**
     * @brief Moves all cards from the play area into the player's bank.
     *
     * Calls willAddToBank() on each card before moving it. If the play area
     * contains both a Chest and a Key, bonus cards are drawn from the discard pile.
     *
     * @param game The current game instance.
     */
    void bankPlayArea(Game& game);

    /**
     * @brief Returns whether the current play area contains two cards of the same suit.
     *
     * @return true if the player is bust, false otherwise.
     */
    [[nodiscard]] bool isBust() const;

    /**
     * @brief Discards all cards from the play area to the given collection.
     *
     * Called when a player busts; all play area cards go to the shared discard pile.
     *
     * @param discardPile The collection to receive the discarded cards.
     */
    void discardPlayArea(CardCollection& discardPile);

    /**
     * @brief Calculates the player's score from their bank.
     *
     * The score is the sum of the highest-value card for each suit present in the bank.
     *
     * @return The total score.
     */
    [[nodiscard]] int calculateScore() const;

    /**
     * @brief Prints the player's name, bank contents grouped by suit, and total score.
     */
    void printBank() const;

    /**
     * @brief Prints the current play area contents grouped by suit.
     */
    void printPlayArea() const;

    /**
     * @brief Returns the player's name.
     *
     * @return A const reference to the player's name string.
     */
    [[nodiscard]] const std::string& name() const;

    /**
     * @brief Returns a const reference to the player's play area.
     *
     * @return The play area card collection.
     */
    [[nodiscard]] const CardCollection& playArea() const;

    /**
     * @brief Returns a const reference to the player's bank.
     *
     * @return The bank card collection.
     */
    [[nodiscard]] const CardCollection& bank() const;

    /**
     * @brief Returns a mutable reference to the player's play area.
     *
     * @return The play area card collection.
     */
    CardCollection& playArea();

    /**
     * @brief Returns a mutable reference to the player's bank.
     *
     * @return The bank card collection.
     */
    CardCollection& bank();

private:
    std::string _name;        /**<The player's display name. */
    CardCollection _playArea; /**<Cards in the current play area. */
    CardCollection _bank;     /**<Cards permanently banked. */

    /**
     * @brief Prints a card collection grouped by suit, with values sorted descending.
     *
     * @param collection The card collection to print.
     */
    static void printCollection(const CardCollection& collection);
};

#endif
