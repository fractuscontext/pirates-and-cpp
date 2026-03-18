#include "Game.hpp"
#include "AnchorCard.hpp"
#include "CannonCard.hpp"
#include "ChestCard.hpp"
#include "HookCard.hpp"
#include "KeyCard.hpp"
#include "KrakenCard.hpp"
#include "MapCard.hpp"
#include "MermaidCard.hpp"
#include "OracleCard.hpp"
#include "SwordCard.hpp"
#include <algorithm>
#include <iostream>
#include <random>

Game::Game()
    : _player1(nullptr), _player2(nullptr), _currentTurn(1), _totalTurns(20),
      _isGameOver(false), _currentPlayer(nullptr) {}

Game::~Game() { _cleanup(); }

Game& Game::instance() {
    static Game _instance;
    return _instance;
}

void Game::init() {
    _cleanup();
    _createDeck();
    shuffleDeck();

    std::string names[] = {"Sam", "Billy", "Jen",   "Bob",  "Sally",
                           "Joe", "Sue",   "Sasha", "Tina", "Marge"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 9);

    _player1 = new Player(names[dist(gen)]);
    _player2 = new Player(names[dist(gen)]);
    _currentPlayer = _player1;
}

void Game::_createDeck() {
    // 54 cards, 9 suits, 6 cards each
    // Suits: Cannon, Chest, Key, Sword, Hook, Oracle, Map, Mermaid, Kraken (Anchor bonus)
    // Values 2-7 for most suits. Mermaid 4-9.
    CardType suits[] = {CardType::Cannon, CardType::Chest,  CardType::Key,
                        CardType::Sword,  CardType::Hook,   CardType::Oracle,
                        CardType::Map,    CardType::Kraken, CardType::Anchor};
    for(auto s : suits) {
        for(int v = 2; v <= 7; ++v) {
            switch(s) {
            case CardType::Cannon:
                _deck.push_back(new CannonCard(v));
                break;
            case CardType::Chest:
                _deck.push_back(new ChestCard(v));
                break;
            case CardType::Key:
                _deck.push_back(new KeyCard(v));
                break;
            case CardType::Sword:
                _deck.push_back(new SwordCard(v));
                break;
            case CardType::Hook:
                _deck.push_back(new HookCard(v));
                break;
            case CardType::Oracle:
                _deck.push_back(new OracleCard(v));
                break;
            case CardType::Map:
                _deck.push_back(new MapCard(v));
                break;
            case CardType::Kraken:
                _deck.push_back(new KrakenCard(v));
                break;
            case CardType::Anchor:
                _deck.push_back(new AnchorCard(v));
                break;
            default:
                break;
            }
        }
    }
    // Mermaid suit: 4, 5, 6, 7, 8, 9
    for(int v = 4; v <= 9; ++v) {
        _deck.push_back(new MermaidCard(v));
    }
}

void Game::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_deck.begin(), _deck.end(), g);
}

void Game::start() {
    while(!_isGameOver) {
        std::cout << "Round " << ((_currentTurn + 1) / 2) << ", Turn "
                  << _currentTurn << std::endl;
        std::cout << "Current Player: " << _currentPlayer->name() << std::endl;
        _currentPlayer->printBank();

        // Initial draw
        drawCard(*_currentPlayer);

        bool drawing = true;
        while(drawing && !_isGameOver && !_currentPlayer->isBust()) {
            _currentPlayer->printPlayArea();
            std::cout << "Draw again? (y/n): ";
            std::string choice;
            std::cin >> choice;
            if(choice == "y") {
                drawCard(*_currentPlayer);
            } else {
                drawing = false;
            }
        }

        if(_currentPlayer->isBust()) {
            std::cout << "BUST!" << std::endl;
            _currentPlayer->discardPlayArea(_discardPile);
        } else {
            _currentPlayer->bankPlayArea(*this);
        }

        nextTurn();
    }
}

void Game::drawCard(Player& player) {
    if(_deck.empty()) {
        _isGameOver = true;
        return;
    }
    Card* card = _deck.back();
    _deck.pop_back();
    std::cout << "Drew: " << card->str() << std::endl;
    bool bust = player.playCard(card, *this);
    if(bust) {
        std::cout << "Bust on drawing " << card->str() << "!" << std::endl;
    }
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
    std::cout << "Game Over!" << std::endl;
    _player1->printBank();
    _player2->printBank();
    int s1 = _player1->calculateScore();
    int s2 = _player2->calculateScore();
    if(s1 > s2) {
        std::cout << _player1->name() << " wins!" << std::endl;
    } else if(s2 > s1) {
        std::cout << _player2->name() << " wins!" << std::endl;
    } else {
        std::cout << "It's a tie!" << std::endl;
    }
}

void Game::_cleanup() {
    for(auto c : _deck) {
        delete c;
    }
    for(auto c : _discardPile) {
        delete c;
    }
    _deck.clear();
    _discardPile.clear();
    delete _player1;
    delete _player2;
    _player1 = _player2 = nullptr;
}

Card* Game::topDeck() { return _deck.empty() ? nullptr : _deck.back(); }
Card* Game::popDeck() {
    if(_deck.empty()) {
        return nullptr;
    }
    Card* c = _deck.back();
    _deck.pop_back();
    return c;
}

CardCollection& Game::deck() { return _deck; }
CardCollection& Game::discardPile() { return _discardPile; }
Player& Game::currentPlayer() { return *_currentPlayer; }
Player& Game::otherPlayer() {
    return (_currentPlayer == _player1) ? *_player2 : *_player1;
}
int Game::turn() const { return _currentTurn; }
int Game::round() const { return (_currentTurn + 1) / 2; }
