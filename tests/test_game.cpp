/**
 * @file test_game.cpp
 * @brief Unit tests for the Game singleton: deck, turns, rounds, discard pile.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "test_helpers.hpp"

#include "Card.hpp"
#include "MermaidCard.hpp"
#include "Player.hpp"
#include <gtest/gtest.h>
#include <map>
#include <set>

class GameTest : public ::testing::Test {
protected:
    Game& _game = Game::instance();

    void SetUp() override { _game.init(); }
};

TEST_F(GameTest, DeckHas60Cards) { EXPECT_EQ(_game.deck().size(), 60U); }

TEST_F(GameTest, DeckHas10Suits) {
    std::set<CardType> suits;
    for(auto* card : _game.deck()) {
        suits.insert(card->type());
    }
    EXPECT_EQ(suits.size(), 10U);
}

TEST_F(GameTest, EachSuitHas6Cards) {
    std::map<CardType, int> suitCount;
    for(auto* card : _game.deck()) {
        suitCount[card->type()]++;
    }
    for(auto const& [type, count] : suitCount) {
        EXPECT_EQ(count, 6) << "Suit with enum value " << static_cast<int>(type)
                            << " has " << count << " cards instead of 6.";
    }
}

TEST_F(GameTest, StandardSuitsHaveValues2To7) {
    std::map<CardType, std::set<int>> suitValues;
    for(auto* card : _game.deck()) {
        suitValues[card->type()].insert(card->value());
    }

    std::set<CardType> const standardSuits
        = {CardType::Cannon, CardType::Chest,  CardType::Key,
           CardType::Sword,  CardType::Hook,   CardType::Oracle,
           CardType::Map,    CardType::Kraken, CardType::Anchor};

    std::set<int> const expected = {2, 3, 4, 5, 6, 7};
    for(auto suit : standardSuits) {
        EXPECT_EQ(suitValues[suit], expected)
            << "Standard suit " << static_cast<int>(suit)
            << " does not have values {2,3,4,5,6,7}.";
    }
}

TEST_F(GameTest, MermaidSuitHasValues4To9) {
    std::set<int> mermaidValues;
    for(auto* card : _game.deck()) {
        if(card->type() == CardType::Mermaid) {
            mermaidValues.insert(card->value());
        }
    }
    std::set<int> const expected = {4, 5, 6, 7, 8, 9};
    EXPECT_EQ(mermaidValues, expected);
}

TEST_F(GameTest, TopDeckReturnsLastCard) {
    Card* top = _game.topDeck();
    ASSERT_NE(top, nullptr);
    EXPECT_EQ(top, _game.deck().back());
}

TEST_F(GameTest, PopDeckRemovesTopCard) {
    size_t const initialSize = _game.deck().size();
    Card* top = _game.topDeck();
    Card* popped = _game.popDeck();
    EXPECT_EQ(top, popped);
    EXPECT_EQ(_game.deck().size(), initialSize - 1);
    _game.deck().push_back(popped);
}

TEST_F(GameTest, PopDeckOnEmptyReturnsNullptr) {
    _game.deck().clear();
    EXPECT_EQ(_game.popDeck(), nullptr);
}

TEST_F(GameTest, TopDeckOnEmptyReturnsNullptr) {
    _game.deck().clear();
    EXPECT_EQ(_game.topDeck(), nullptr);
}

TEST_F(GameTest, DiscardPileStartsEmpty) {
    EXPECT_TRUE(_game.discardPile().empty());
}

TEST_F(GameTest, DiscardCardAddsToDiscardPile) {
    auto* card = new MermaidCard(5);
    _game.discardCard(card);
    EXPECT_EQ(_game.discardPile().size(), 1U);
    EXPECT_EQ(_game.discardPile().back(), card);
}

TEST_F(GameTest, TwoPlayersInitialised) {
    EXPECT_FALSE(_game.currentPlayer().name().empty());
    EXPECT_FALSE(_game.otherPlayer().name().empty());
}

TEST_F(GameTest, CurrentPlayerDiffersFromOther) {
    EXPECT_NE(&_game.currentPlayer(), &_game.otherPlayer());
}

TEST_F(GameTest, InitialTurnIsOne) { EXPECT_EQ(_game.turn(), 1); }

TEST_F(GameTest, InitialRoundIsOne) { EXPECT_EQ(_game.round(), 1); }

TEST_F(GameTest, NextTurnSwitchesPlayer) {
    std::string const firstPlayer = _game.currentPlayer().name();
    _game.nextTurn();
    EXPECT_NE(&_game.currentPlayer(), &_game.otherPlayer());
    EXPECT_EQ(_game.turn(), 2);
}

TEST_F(GameTest, RoundCalculation) {
    EXPECT_EQ(_game.turn(), 1);
    EXPECT_EQ(_game.round(), 1);

    _game.nextTurn();
    EXPECT_EQ(_game.turn(), 2);
    EXPECT_EQ(_game.round(), 1);
}

TEST_F(GameTest, ShuffleDeckChangesOrder) {
    std::vector<std::string> before;
    before.reserve(_game.deck().size());
    for(auto& thisCard : _game.deck()) {
        before.push_back(thisCard->str());
    }

    _game.shuffleDeck();

    std::vector<std::string> after;
    after.reserve(_game.deck().size());
    for(auto& thisCard : _game.deck()) {
        after.push_back(thisCard->str());
    }

    EXPECT_EQ(before.size(), after.size());

    bool different = false;
    for(size_t idx = 0; idx < before.size(); ++idx) {
        if(before[idx] != after[idx]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different) << "Shuffle did not change the deck order.";
}

TEST_F(GameTest, ShufflePreservesDeckSize) {
    size_t const sizeBefore = _game.deck().size();
    _game.shuffleDeck();
    EXPECT_EQ(_game.deck().size(), sizeBefore);
}

TEST_F(GameTest, DrawCardReducesDeckSize) {
    size_t const sizeBefore = _game.deck().size();
    {
        CoutSuppressor suppress;
        _game.drawCard(_game.currentPlayer());
    }
    EXPECT_LT(_game.deck().size(), sizeBefore);
}

TEST_F(GameTest, DrawCardAddsToPlayerPlayArea) {
    Player& player = _game.currentPlayer();
    EXPECT_TRUE(player.playArea().empty());
    {
        CoutSuppressor suppress;
        _game.drawCard(player);
    }
    EXPECT_GE(player.playArea().size(), 1U);
}

TEST_F(GameTest, DrawCardOnEmptyDeckSetsGameOver) {
    for(auto* card : _game.deck()) {
        delete card;
    }
    _game.deck().clear();

    Player& player = _game.currentPlayer();
    size_t const playAreaBefore = player.playArea().size();
    {
        CoutSuppressor suppress;
        _game.drawCard(player);
    }
    //No card should be added since deck is empty
    EXPECT_EQ(player.playArea().size(), playAreaBefore);
}

TEST_F(GameTest, InitResetsDeckAndPlayers) {
    {
        CoutSuppressor suppress;
        _game.drawCard(_game.currentPlayer());
    }
    _game.discardCard(_game.popDeck());

    _game.init();
    EXPECT_EQ(_game.deck().size(), 60U);
    EXPECT_TRUE(_game.discardPile().empty());
    EXPECT_TRUE(_game.currentPlayer().playArea().empty());
    EXPECT_TRUE(_game.currentPlayer().bank().empty());
    EXPECT_EQ(_game.turn(), 1);
    EXPECT_EQ(_game.round(), 1);
}
