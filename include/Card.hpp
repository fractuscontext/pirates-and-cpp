#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

class Game;
class Player;

enum class CardType {
    Cannon,
    Chest,
    Key,
    Sword,
    Hook,
    Oracle,
    Map,
    Mermaid,
    Kraken,
    Anchor
};

class Card {
public:
    Card(CardType type, int value);
    virtual ~Card();

    [[nodiscard]] virtual std::string str() const = 0;
    virtual void play(Game& game, Player& player) = 0;
    virtual void willAddToBank(Game& /*game*/, Player& /*player*/) {}
    [[nodiscard]] CardType type() const;
    [[nodiscard]] int value() const;

protected:
    CardType _type;
    int _value;
};

using CardCollection = std::vector<Card*>;

#endif
