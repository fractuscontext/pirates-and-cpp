#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include "Player.hpp"
#include <random>
#include <string>
#include <vector>

class Game {
public:
    static Game& instance();

    void init();
    void start();
    void end();

    void nextTurn();
    void drawCard(Player& player);
    void discardCard(Card* card);
    void shuffleDeck();

    Card* topDeck();
    Card* popDeck();

    CardCollection& deck();
    CardCollection& discardPile();
    Player& currentPlayer();
    Player& otherPlayer();

    int turn() const;
    int round() const;

private:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void _createDeck();
    void _cleanup();

    CardCollection _deck;
    CardCollection _discardPile;
    Player* _player1;
    Player* _player2;
    int _currentTurn;
    int _totalTurns;
    bool _isGameOver;
    Player* _currentPlayer;
};

#endif
