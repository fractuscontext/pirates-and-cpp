/**
 * @file Game.cpp
 * @brief Implements the Game singleton and game loop.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "Game.hpp"
#include "AnchorCard.hpp"
#include "CannonCard.hpp"
#include "ChestCard.hpp"
#include "HookCard.hpp"
#include "InputHelper.hpp"
#include "KeyCard.hpp"
#include "KrakenCard.hpp"
#include "MapCard.hpp"
#include "MermaidCard.hpp"
#include "OracleCard.hpp"
#include "SwordCard.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>

Game::Game() = default;

Game::~Game() { cleanup(); }

Game& Game::instance() {
    static Game instance;
    return instance;
}

void Game::init() {
    cleanup();
    createDeck();
    shuffleDeck();

    _player1 = new Player();
    _player2 = new Player();
    _currentPlayer = _player1;
}

void Game::createDeck() {
    //54 cards, 9 suits, 6 cards each
    //Suits: Cannon, Chest, Key, Sword, Hook, Oracle, Map, Mermaid, Kraken (Anchor bonus)
    //Values 2-7 for most suits. Mermaid 4-9.
    std::array<CardType, 9> const suits
        = {CardType::Cannon, CardType::Chest,  CardType::Key,
           CardType::Sword,  CardType::Hook,   CardType::Oracle,
           CardType::Map,    CardType::Kraken, CardType::Anchor};
    for(auto suit : suits) {
        for(int val = 2; val <= 7; ++val) {
            switch(suit) {
            case CardType::Cannon:
                _deck.push_back(new CannonCard(val));
                break;
            case CardType::Chest:
                _deck.push_back(new ChestCard(val));
                break;
            case CardType::Key:
                _deck.push_back(new KeyCard(val));
                break;
            case CardType::Sword:
                _deck.push_back(new SwordCard(val));
                break;
            case CardType::Hook:
                _deck.push_back(new HookCard(val));
                break;
            case CardType::Oracle:
                _deck.push_back(new OracleCard(val));
                break;
            case CardType::Map:
                _deck.push_back(new MapCard(val));
                break;
            case CardType::Kraken:
                _deck.push_back(new KrakenCard(val));
                break;
            case CardType::Anchor:
                _deck.push_back(new AnchorCard(val));
                break;
            default:
                break;
            }
        }
    }
    //Mermaid suit: 4, 5, 6, 7, 8, 9
    for(int val = 4; val <= 9; ++val) {
        _deck.push_back(new MermaidCard(val));
    }
}

void Game::shuffleDeck() {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::shuffle(_deck.begin(), _deck.end(), gen);
}

void Game::start() {
    while(!_isGameOver) {
        std::cout << "-- Round " << ((_currentTurn + 1) / 2) << ", Turn "
                  << _currentTurn << " ---\n";
        std::cout << _currentPlayer->name() << "'s turn.\n";
        _currentPlayer->printBank();

        //Initial draw
        drawCard(*_currentPlayer);

        bool drawing = true;
        while(drawing && !_isGameOver && !_currentPlayer->isBust()) {
            _currentPlayer->printPlayArea();
            if(InputHelper::askYesNo("Draw again? (y/n): ")) {
                drawCard(*_currentPlayer);
            } else {
                drawing = false;
            }
        }

        if(_currentPlayer->isBust()) {
            std::cout << "BUST! " << _currentPlayer->name()
                      << " loses all cards in play area.\n";
            _currentPlayer->discardPlayArea(_discardPile);
        } else {
            _currentPlayer->bankPlayArea(*this);
            _currentPlayer->printBank();
        }

        nextTurn();
    }
}

void Game::drawCard(Player& player) {
    if(_deck.empty()) {
        _isGameOver = true;
        return;
    }
    Card* const card = _deck.back();
    _deck.pop_back();
    std::cout << player.name() << " draws a " << card->str() << '\n';
    player.playCard(card, *this);
}

void Game::nextTurn() {
    _currentTurn++;
    if(_currentTurn > _totalTurns || _deck.empty()) {
        _isGameOver = true;
        end();
    } else {
        _currentPlayer = (_currentPlayer == _player1) ? _player2 : _player1;
    }
}

void Game::end() {
    std::cout << "--- Game Over ---\n";
    _player1->printBank();
    _player2->printBank();
    int const score1 = _player1->calculateScore();
    int const score2 = _player2->calculateScore();
    if(score1 > score2) {
        std::cout << _player1->name() << " wins!" << '\n';
    } else if(score2 > score1) {
        std::cout << _player2->name() << " wins!" << '\n';
    } else {
        std::cout << "It's a tie!" << '\n';
    }
}

void Game::cleanup() {
    for(auto* card : _deck) {
        delete card;
    }
    for(auto* card : _discardPile) {
        delete card;
    }
    _deck.clear();
    _discardPile.clear();
    delete _player1;
    delete _player2;
    _player1 = _player2 = nullptr;
}

Card* Game::topDeck() const { return _deck.empty() ? nullptr : _deck.back(); }
Card* Game::popDeck() {
    if(_deck.empty()) {
        return nullptr;
    }
    Card* const card = _deck.back();
    _deck.pop_back();
    return card;
}

void Game::discardCard(Card* card) { _discardPile.push_back(card); }

CardCollection& Game::deck() { return _deck; }
CardCollection& Game::discardPile() { return _discardPile; }
Player& Game::currentPlayer() { return *_currentPlayer; }
Player& Game::otherPlayer() {
    return (_currentPlayer == _player1) ? *_player2 : *_player1;
}
int Game::turn() const { return _currentTurn; }
int Game::round() const { return (_currentTurn + 1) / 2; }
