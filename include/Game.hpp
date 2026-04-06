/**
 * @file Game.hpp
 * @brief Declares the Game singleton that drives Dead Man's Draw++.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include "Player.hpp"
#include "RandomProvider.hpp"

/**
 * @brief Singleton class responsible for controlling the entire game flow.
 *
 * The Game object initialises the deck and players, runs the turn loop,
 * handles drawing cards, busting, banking, and ultimately determines the winner.
 * Only one instance may exist at any time (Meyer's singleton).
 */
class Game {
public:
    /**
     * @brief Returns the singleton Game instance.
     *
     * @return A reference to the single Game object.
     */
    static Game& instance();

    /**
     * @brief Initialises a new game: creates and shuffles the deck and sets up two players.
     *
     * Any previous game state is cleaned up before reinitialisation.
     */
    void init();

    /**
     * @brief Initialises a new game with explicit player names.
     *
     * Useful for deterministic testing — names are not randomly chosen.
     *
     * @param name1 Name for the first player.
     * @param name2 Name for the second player.
     */
    void init(const std::string& name1, const std::string& name2);

    /**
     * @brief Sets a custom random provider for shuffling and name generation.
     *
     * Pass nullptr to revert to the default provider. Must be called before
     * init() for the provider to take effect.
     *
     * @param provider Pointer to a provider (Game does NOT take ownership).
     */
    void setRandomProvider(RandomProvider* provider);

    /**
     * @brief Starts and runs the main game loop until the game ends.
     *
     * Each iteration represents one player's turn: drawing cards, prompting for
     * additional draws, handling busts, and banking loot.
     */
    void start();

    /**
     * @brief Ends the game and prints final bank summaries and the winner.
     */
    void end();

    /**
     * @brief Advances to the next turn, switching the current player.
     *
     * If the maximum turn count is reached or the deck is empty, the game ends.
     */
    void nextTurn();

    /**
     * @brief Draws the top card from the deck and plays it for the given player.
     *
     * If the deck is empty, the game is flagged as over and no card is drawn.
     *
     * @param player The player drawing the card.
     */
    void drawCard(Player& player);

    /**
     * @brief Moves a card onto the discard pile.
     *
     * @param card Pointer to the card to discard.
     */
    void discardCard(Card* card);

    /**
     * @brief Shuffles the deck in place using a Mersenne Twister seeded by a random device.
     */
    void shuffleDeck();

    /**
     * @brief Returns a pointer to the top card of the deck without removing it.
     *
     * @return Pointer to the top card, or nullptr if the deck is empty.
     */
    [[nodiscard]] Card* topDeck() const;

    /**
     * @brief Removes and returns the top card from the deck.
     *
     * @return Pointer to the removed card, or nullptr if the deck is empty.
     */
    Card* popDeck();

    /**
     * @brief Returns a mutable reference to the deck.
     *
     * @return Reference to the card collection representing the deck.
     */
    CardCollection& deck();

    /**
     * @brief Returns a mutable reference to the discard pile.
     *
     * @return Reference to the card collection representing the discard pile.
     */
    CardCollection& discardPile();

    /**
     * @brief Returns a reference to the player whose turn it currently is.
     *
     * @return Reference to the current player.
     */
    Player& currentPlayer();

    /**
     * @brief Returns a reference to the player who is not currently taking a turn.
     *
     * @return Reference to the other player.
     */
    Player& otherPlayer();

    /**
     * @brief Returns the current turn number (1-based, increments each player's turn).
     *
     * @return The current turn number.
     */
    [[nodiscard]] int turn() const;

    /**
     * @brief Returns the current round number (two turns per round).
     *
     * @return The current round number.
     */
    [[nodiscard]] int round() const;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

private:
    /** @brief Private constructor for singleton pattern. */
    Game();
    /** @brief Destructor. Cleans up all game resources. */
    ~Game();

    /** @brief Creates the 60-card deck with all suits and values. */
    void createDeck();
    /** @brief Frees all allocated cards and players. */
    void cleanup();
    /**
     * @brief Returns the active random provider (injected or default).
     * @return Reference to the current RandomProvider.
     */
    RandomProvider& randomProvider();

    CardCollection _deck;        /**<The shared deck of cards. */
    CardCollection _discardPile; /**<The shared discard pile. */
    Player* _player1{nullptr};   /**<Pointer to the first player. */
    Player* _player2{nullptr};   /**<Pointer to the second player. */
    int _currentTurn{1};         /**<The current turn number. */
    int _totalTurns{20}; /**<Maximum number of turns before the game ends. */
    bool _isGameOver{false}; /**<Whether the game has ended. */
    Player* _currentPlayer{
        nullptr}; /**<Pointer to the player whose turn it is. */
    RandomProvider* _randomProvider{
        nullptr}; /**<Injected RNG (nullptr = use default). */
    DefaultRandomProvider
        _defaultProvider; /**<Owned default provider instance. */
};

#endif
