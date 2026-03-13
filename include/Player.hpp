#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include <map>
#include <string>
#include <vector>

class Game;

class Player {
public:
    explicit Player(std::string name);
    ~Player();

    bool playCard(Card* card, Game& game);
    void bankPlayArea(Game& game);
    [[nodiscard]] bool isBust() const;
    void discardPlayArea(CardCollection& discardPile);

    [[nodiscard]] int calculateScore() const;
    void printBank() const;
    void printPlayArea() const;

    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] const CardCollection& playArea() const;
    [[nodiscard]] const CardCollection& bank() const;

private:
    std::string _name;
    CardCollection _playArea;
    CardCollection _bank;

    static void printCollection(const CardCollection& collection) ;
};

#endif
