/**
 * @file Player.cpp
 * @brief Implements the Player class.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "Player.hpp"
#include "Card.hpp"
#include "Game.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>

Player::Player() {
    std::array<std::string, 10> const names
        = {"Sam", "Billy", "Jen",   "Bob",  "Sally",
           "Joe", "Sue",   "Sasha", "Tina", "Marge"};
    _name = names.at(
        rand()
        % 10); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
}

Player::Player(std::string name) : _name(std::move(name)) {}

Player::~Player() {
    for(auto* card : _playArea) {
        delete card;
    }
    for(auto* card : _bank) {
        delete card;
    }
}

bool Player::playCard(Card* card, Game& game) {
    bool const bust = _bustChecker.wouldBust(card->type());
    _playArea.push_back(card);
    _bustChecker.recordCard(card->type());

    if(bust) {
        _bustChecker.setBust();
        return true;
    }

    card->play(game, *this);
    return false;
}

bool Player::isBust() const { return _bustChecker.isBust(); }

void Player::bankPlayArea(Game& game) {
    for(auto* card : _playArea) {
        card->willAddToBank(game, *this);
        _bank.push_back(card);
    }
    _playArea.clear();
    _bustChecker.reset();
}

void Player::discardPlayArea(CardCollection& discardPile) {
    for(auto* card : _playArea) {
        discardPile.push_back(card);
    }
    _playArea.clear();
    _bustChecker.reset();
}

int Player::calculateScore() const {
    std::map<CardType, int> maxValues;
    for(auto* card : _bank) {
        if(!maxValues.contains(card->type())
           || card->value() > maxValues[card->type()]) {
            maxValues[card->type()] = card->value();
        }
    }
    int total = 0;
    for(auto const& [type, val] : maxValues) {
        total += val;
    }
    return total;
}

void Player::printBank() const {
    std::cout << _name << "'s Bank:\n";
    printCollection(_bank);
    std::cout << "| Score: " << calculateScore() << "\n\n";
}

void Player::printPlayArea() const {
    std::cout << _name << "'s Play Area:\n";
    printCollection(_playArea);
}

void Player::printCollection(const CardCollection& collection) {
    if(collection.empty()) {
        std::cout << " (empty)" << '\n';
        return;
    }
    //Group by suit, sorted by value
    std::map<CardType, std::vector<int>> grouped;
    for(auto* card : collection) {
        grouped[card->type()].push_back(card->value());
    }
    for(auto& pair : grouped) {
        std::ranges::sort(pair.second, std::greater<>());
        std::string suitName;
        switch(pair.first) {
        case CardType::Cannon:
            suitName = "Cannon";
            break;
        case CardType::Chest:
            suitName = "Chest";
            break;
        case CardType::Key:
            suitName = "Key";
            break;
        case CardType::Sword:
            suitName = "Sword";
            break;
        case CardType::Hook:
            suitName = "Hook";
            break;
        case CardType::Oracle:
            suitName = "Oracle";
            break;
        case CardType::Map:
            suitName = "Map";
            break;
        case CardType::Mermaid:
            suitName = "Mermaid";
            break;
        case CardType::Kraken:
            suitName = "Kraken";
            break;
        case CardType::Anchor:
            suitName = "Anchor";
            break;
        }
        for(size_t idx = 0; idx < pair.second.size(); ++idx) {
            if(idx > 0) {
                std::cout << ' ';
            } else {
                std::cout << '\t';
            }
            std::cout << suitName << '(' << pair.second[idx] << ')';
        }
        std::cout << '\n';
    }
}

const std::string& Player::name() const { return _name; }
const CardCollection& Player::playArea() const { return _playArea; }
const CardCollection& Player::bank() const { return _bank; }
CardCollection& Player::playArea() { return _playArea; }
CardCollection& Player::bank() { return _bank; }
BustChecker& Player::bustChecker() { return _bustChecker; }
