/**
 * @file MermaidCard.hpp
 * @brief Declares the MermaidCard class for the Mermaid suit.
 */
#ifndef MERMAID_CARD_HPP
#define MERMAID_CARD_HPP

#include "Card.hpp"

/**
 * @brief Represents a Mermaid card.
 *
 * Has no special ability, but carries higher point values (4–9) compared
 * to most other suits (2–7), making it particularly valuable to bank.
 */
class MermaidCard : public Card {
public:
    /**
     * @brief Constructs a MermaidCard with the given point value.
     *
     * @param val The point value of this card (4–9).
     */
    explicit MermaidCard(int val);

    /**
     * @brief Returns the string representation of this card.
     *
     * @return A string in the format "Mermaid(value)".
     */
    [[nodiscard]] std::string str() const override;

    /**
     * @brief No ability; this card has no special effect when drawn.
     *
     * @param game   The current game instance.
     * @param player The player who drew this card.
     */
    void play(Game& game, Player& player) override;
};

#endif
