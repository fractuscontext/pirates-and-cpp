/**
 * @file Card.cpp
 * @brief Implements the Card base class.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "Card.hpp"

Card::Card(CardType type, int value) : _type(type), _value(value) {}
Card::~Card() = default;

const CardType& Card::type() const { return _type; }

int Card::value() const { return _value; }
