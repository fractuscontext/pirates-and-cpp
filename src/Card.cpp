#include "Card.hpp"

Card::Card(CardType type, int value) : _type(type), _value(value) {}
Card::~Card() = default;

const CardType& Card::type() const { return _type; }

int Card::value() const { return _value; }
