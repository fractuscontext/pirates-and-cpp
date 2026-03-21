/**
 * @file SwordCard.hpp
 * @brief Declares the SwordCard class for the Sword suit.
 */
#ifndef SWORD_CARD_HPP
#define SWORD_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Sword card.
 *
 * When played, the player selects a suit and steals the highest-value card
 * of that suit from the opponent's bank into their own play area.
 * The stolen card's ability is also triggered and may cause a bust.
 */
class SwordCard : public Card {
public:
    /**
     * @brief Constructs a SwordCard with the given point value.
     *
     * @param val The point value of this card (2–7).
     */
    explicit SwordCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Sword(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief Prompts the player to choose a suit and steals the top card of that suit from the opponent's bank.
     *
     * If the opponent's bank is empty, a message is printed and the ability is skipped.
     * The stolen card is played into the current player's play area; a bust may result.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
