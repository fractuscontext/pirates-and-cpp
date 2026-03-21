/**
 * @file Card.hpp
 * @brief Defines the abstract Card base class and the CardType enumeration.
 */
#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

class Game;
class Player;

/**
 * @brief Enumeration of all card suits in Dead Man's Draw++.
 */
enum class CardType {
    Cannon, /**<Discards the top card of a chosen suit from the opponent's bank. */
    Chest, /**<No immediate effect; grants bonus draws when banked with a Key. */
    Key, /**<No immediate effect; activates the Chest bonus when banked together. */
    Sword, /**<Steals the top card of a chosen suit from the opponent's bank. */
    Hook, /**<Returns the top card of a chosen suit from the player's own bank. */
    Oracle, /**<Reveals the top card of the deck before the player decides to draw again. */
    Map, /**<Draws three cards from the discard pile; the player must play one. */
    Mermaid, /**<No ability; higher point values (4–9) compared to other suits. */
    Kraken, /**<Forces the player to draw and play three consecutive cards. */
    Anchor  /**<Cards drawn before this are saved to the bank even on a bust. */
};

/**
 * @brief Abstract base class representing a single card in the game.
 *
 * Each card has a suit (CardType) and a point value. Concrete subclasses
 * override play() to implement their special ability, and may override
 * willAddToBank() for abilities that fire only when the player banks their cards.
 */
class Card {
public:
    /**
     * @brief Constructs a Card with the given suit and point value.
     *
     * @param type  The suit of the card.
     * @param value The point value of the card.
     */
    Card(CardType type, int value);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Card();

    /**
     * @brief Returns a human-readable string for this card.
     *
     * @return A string in the format "SuitName(value)", e.g. "Oracle(7)".
     */
    [[nodiscard]] virtual std::string str() const = 0;

    /**
     * @brief Executes this card's special ability.
     *
     * Called after the card is added to the play area, provided no bust
     * occurred. Override in each concrete subclass to implement its unique ability.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    virtual void play(Game& game, Player& player) = 0;

    /**
     * @brief Called just before this card is moved into the player's bank.
     *
     * Override to implement banking-time effects (e.g. Chest/Key combo).
     * The default implementation does nothing.
     *
     * @param game   The current game instance.
     * @param player The player who is banking this card.
     */
    virtual void willAddToBank(Game& /*game*/, Player& /*player*/) {}

    /**
     * @brief Returns the suit type of this card.
     *
     * @return A const reference to this card's CardType.
     */
    [[nodiscard]] const CardType& type() const;

    /**
     * @brief Returns the point value of this card.
     *
     * @return The integer point value.
     */
    [[nodiscard]] int value() const;

protected:
    CardType _type; /**<The suit of this card. */
    int _value;     /**<The point value of this card. */
};

/**
 * @brief Alias for a collection of card pointers used throughout the game.
 */
using CardCollection = std::vector<Card*>;

#endif
