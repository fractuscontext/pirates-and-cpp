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
#include <set>

Player::Player() {
    std::array<std::string, 10> const names
        = {"Sam", "Billy", "Jen",   "Bob",  "Sally",
           "Joe", "Sue",   "Sasha", "Tina", "Marge"};
    _name = names.at(
        rand()
        % 10); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
}

Player::~Player() {
    for(auto* card : _playArea) {
        delete card;
    }
    for(auto* card : _bank) {
        delete card;
    }
}

bool Player::playCard(Card* card, Game& game) {
    //Check if drawing this card causes a bust
    for(auto* existing : _playArea) {
        if(existing->type() == card->type()) {
            _playArea.push_back(card);
            return true; //Bust
        }
    }
    _playArea.push_back(card);
    card->play(game, *this);
    return false;
}

bool Player::isBust() const {
    std::set<CardType> seen;
    for(auto* card : _playArea) {
        if(seen.contains(card->type())) {
            return true;
        }
        seen.insert(card->type());
    }
    return false;
}

void Player::bankPlayArea(Game& game) {
    //Collect all cards currently in the play area
    //Chest/Key logic check before adding
    bool hasChest = false;
    bool hasKey = false;
    for(auto* card : _playArea) {
        if(card->type() == CardType::Chest) {
            hasChest = true;
        }
        if(card->type() == CardType::Key) {
            hasKey = true;
        }
    }

    int bonusCount = 0;
    if(hasChest && hasKey) {
        bonusCount = static_cast<int>(_playArea.size());
    }

    for(auto* card : _playArea) {
        card->willAddToBank(game, *this);
        _bank.push_back(card);
    }
    _playArea.clear();

    if(bonusCount > 0) {
        std::cout << "Chest and Key combination! Drawing " << bonusCount
                  << " bonus cards from discard." << '\n';
        //Drawing from discard pile to bank
        for(int i = 0; i < bonusCount && !game.discardPile().empty(); ++i) {
            Card* const bonus = game.discardPile().back();
            game.discardPile().pop_back();
            _bank.push_back(bonus);
            std::cout << "Added " << bonus->str() << " to bank." << '\n';
        }
    }
}

void Player::discardPlayArea(CardCollection& discardPile) {
    for(auto* card : _playArea) {
        discardPile.push_back(card);
    }
    _playArea.clear();
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
    if(_bank.empty()) {
        std::cout << " (empty)\n";
    } else {
        std::map<CardType, std::vector<int>> grouped;
        for(auto* card : _bank) {
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
            for(size_t i = 0; i < pair.second.size(); ++i) {
                std::cout << suitName << " (" << pair.second[i] << ")"
                          << (i == pair.second.size() - 1 ? "" : " ");
            }
            std::cout << '\n';
        }
    }
    std::cout << "| Score: " << calculateScore() << '\n';
}

void Player::printPlayArea() const {
    std::cout << _name << "'s Play Area:\n";
    if(_playArea.empty()) {
        std::cout << " (empty)\n";
    } else {
        for(auto* card : _playArea) {
            std::cout << card->str() << '\n';
        }
    }
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
        switch(pair.first) {
        case CardType::Cannon:
            std::cout << "Cannon: ";
            break;
        case CardType::Chest:
            std::cout << "Chest: ";
            break;
        case CardType::Key:
            std::cout << "Key: ";
            break;
        case CardType::Sword:
            std::cout << "Sword: ";
            break;
        case CardType::Hook:
            std::cout << "Hook: ";
            break;
        case CardType::Oracle:
            std::cout << "Oracle: ";
            break;
        case CardType::Map:
            std::cout << "Map: ";
            break;
        case CardType::Mermaid:
            std::cout << "Mermaid: ";
            break;
        case CardType::Kraken:
            std::cout << "Kraken: ";
            break;
        case CardType::Anchor:
            std::cout << "Anchor: ";
            break;
        }
        for(size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i]
                      << (i == pair.second.size() - 1 ? "" : ", ");
        }
        std::cout << '\n';
    }
}

const std::string& Player::name() const { return _name; }
const CardCollection& Player::playArea() const { return _playArea; }
const CardCollection& Player::bank() const { return _bank; }
CardCollection& Player::playArea() { return _playArea; }
CardCollection& Player::bank() { return _bank; }
