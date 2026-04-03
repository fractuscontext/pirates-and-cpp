/**
 * @file test_player.cpp
 * @brief Unit tests for the Player class: play area, banking, bust, scoring.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "test_helpers.hpp"

#include "CannonCard.hpp"
#include "ChestCard.hpp"
#include "KeyCard.hpp"
#include "MermaidCard.hpp"
#include "OracleCard.hpp"
#include "Player.hpp"
#include <gtest/gtest.h>
#include <set>
#include <string>

class PlayerTest : public ::testing::Test {
protected:
    Game& _game = Game::instance();

    void SetUp() override { _game.init(); }
};

TEST(PlayerTestStandalone, NameIsFromFixedList) {
    std::set<std::string> const validNames
        = {"Sam", "Billy", "Jen",   "Bob",  "Sally",
           "Joe", "Sue",   "Sasha", "Tina", "Marge"};
    Player player;
    EXPECT_TRUE(validNames.contains(player.name()))
        << "Player name '" << player.name() << "' not in the fixed list.";
}

TEST(PlayerTestStandalone, StartsWithEmptyPlayArea) {
    Player player;
    EXPECT_TRUE(player.playArea().empty());
}

TEST(PlayerTestStandalone, StartsWithEmptyBank) {
    Player player;
    EXPECT_TRUE(player.bank().empty());
}

TEST(PlayerTestStandalone, InitialScoreIsZero) {
    Player player;
    EXPECT_EQ(player.calculateScore(), 0);
}

TEST(PlayerTestStandalone, IsBustEmptyPlayArea) {
    Player player;
    EXPECT_FALSE(player.isBust());
}

TEST(PlayerTestStandalone, ScoreEmptyBankIsZero) {
    Player player;
    EXPECT_EQ(player.calculateScore(), 0);
}

TEST_F(PlayerTest, PlayCardAddsSingleCard) {
    Player& player = _game.currentPlayer();

    auto* card = new MermaidCard(5);
    bool const bust = player.playCard(card, _game);
    EXPECT_FALSE(bust);
    EXPECT_EQ(player.playArea().size(), 1U);
    EXPECT_EQ(player.playArea()[0]->str(), "Mermaid(5)");
}

TEST_F(PlayerTest, PlayCardMultipleDifferentSuitsNoBust) {
    Player& player = _game.currentPlayer();

    auto* mermaid = new MermaidCard(6);
    auto* chest = new ChestCard(3);
    EXPECT_FALSE(player.playCard(mermaid, _game));
    EXPECT_FALSE(player.playCard(chest, _game));
    EXPECT_EQ(player.playArea().size(), 2U);
    EXPECT_FALSE(player.isBust());
}

TEST_F(PlayerTest, PlayCardSameSuitCausesBust) {
    Player& player = _game.currentPlayer();

    auto* mermaid1 = new MermaidCard(5);
    auto* mermaid2 = new MermaidCard(7);
    EXPECT_FALSE(player.playCard(mermaid1, _game));
    EXPECT_TRUE(player.playCard(mermaid2, _game));
    EXPECT_TRUE(player.isBust());
}

TEST_F(PlayerTest, BustDoesNotTriggerAbility) {
    Player& player = _game.currentPlayer();

    auto* oracle1 = new OracleCard(3);
    auto* oracle2 = new OracleCard(6);
    EXPECT_FALSE(player.playCard(oracle1, _game));
    EXPECT_TRUE(player.playCard(oracle2, _game));
    EXPECT_TRUE(player.isBust());
    EXPECT_EQ(player.playArea().size(), 2U);
}

TEST_F(PlayerTest, IsBustSingleCard) {
    Player& player = _game.currentPlayer();
    auto* card = new MermaidCard(4);
    player.playCard(card, _game);
    EXPECT_FALSE(player.isBust());
}

TEST_F(PlayerTest, BankPlayAreaMovesCardsToBank) {
    Player& player = _game.currentPlayer();

    auto* mermaid = new MermaidCard(8);
    auto* chest = new ChestCard(4);
    player.playCard(mermaid, _game);
    player.playCard(chest, _game);
    EXPECT_EQ(player.playArea().size(), 2U);

    player.bankPlayArea(_game);
    EXPECT_TRUE(player.playArea().empty());
    EXPECT_EQ(player.bank().size(), 2U);
}

TEST_F(PlayerTest, BankPlayAreaClearsPlayArea) {
    Player& player = _game.currentPlayer();

    auto* mermaid = new MermaidCard(5);
    player.playCard(mermaid, _game);
    player.bankPlayArea(_game);
    EXPECT_TRUE(player.playArea().empty());
}

TEST_F(PlayerTest, DiscardPlayAreaMovesToDiscardPile) {
    Player& player = _game.currentPlayer();

    auto* mermaid = new MermaidCard(6);
    auto* chest = new ChestCard(2);
    player.playCard(mermaid, _game);
    player.playCard(chest, _game);

    CardCollection discard;
    player.discardPlayArea(discard);
    EXPECT_TRUE(player.playArea().empty());
    EXPECT_EQ(discard.size(), 2U);

    for(auto* card : discard) {
        delete card;
    }
}

TEST_F(PlayerTest, ScoreIsSumOfHighestPerSuit) {
    Player& player = _game.currentPlayer();

    player.bank().push_back(new MermaidCard(8));
    player.bank().push_back(new MermaidCard(5));
    player.bank().push_back(new ChestCard(7));

    EXPECT_EQ(player.calculateScore(), 15);
}

TEST_F(PlayerTest, ScoreWithSingleCardPerSuit) {
    Player& player = _game.currentPlayer();

    player.bank().push_back(new MermaidCard(6));
    player.bank().push_back(new CannonCard(4));
    player.bank().push_back(new KeyCard(3));

    EXPECT_EQ(player.calculateScore(), 13);
}

TEST_F(PlayerTest, ScoreOnlyCountsHighestInEachSuit) {
    Player& player = _game.currentPlayer();

    player.bank().push_back(new CannonCard(2));
    player.bank().push_back(new CannonCard(5));
    player.bank().push_back(new CannonCard(7));

    EXPECT_EQ(player.calculateScore(), 7);
}

TEST_F(PlayerTest, ScoreMultipleSuitsMultipleCards) {
    Player& player = _game.currentPlayer();

    player.bank().push_back(new MermaidCard(4));
    player.bank().push_back(new MermaidCard(9));
    player.bank().push_back(new CannonCard(3));
    player.bank().push_back(new CannonCard(7));
    player.bank().push_back(new KeyCard(5));

    EXPECT_EQ(player.calculateScore(), 21);
}

TEST_F(PlayerTest, ChestKeyBonusDrawsFromDiscard) {
    Player& player = _game.currentPlayer();

    _game.discardCard(new MermaidCard(4));
    _game.discardCard(new CannonCard(3));
    _game.discardCard(new OracleCard(2));

    auto* chest = new ChestCard(5);
    auto* key = new KeyCard(6);
    player.playCard(chest, _game);
    player.playCard(key, _game);

    int const playAreaSize = static_cast<int>(player.playArea().size());
    player.bankPlayArea(_game);

    EXPECT_GE(static_cast<int>(player.bank().size()), playAreaSize);
}

TEST_F(PlayerTest, ChestWithoutKeyNoBonusDraw) {
    Player& player = _game.currentPlayer();

    _game.discardCard(new MermaidCard(4));

    auto* chest = new ChestCard(5);
    player.playCard(chest, _game);
    player.bankPlayArea(_game);

    EXPECT_EQ(player.bank().size(), 1U);
    EXPECT_EQ(_game.discardPile().size(), 1U);
}

TEST_F(PlayerTest, KeyWithoutChestNoBonusDraw) {
    Player& player = _game.currentPlayer();

    _game.discardCard(new MermaidCard(4));

    auto* key = new KeyCard(6);
    player.playCard(key, _game);
    player.bankPlayArea(_game);

    EXPECT_EQ(player.bank().size(), 1U);
    EXPECT_EQ(_game.discardPile().size(), 1U);
}

TEST_F(PlayerTest, ChestKeyBonusLimitedByDiscardSize) {
    Player& player = _game.currentPlayer();

    _game.discardCard(new MermaidCard(4));

    auto* chest = new ChestCard(5);
    auto* key = new KeyCard(6);
    auto* oracle = new OracleCard(3);
    player.playCard(chest, _game);
    player.playCard(key, _game);
    player.playCard(oracle, _game);

    player.bankPlayArea(_game);

    EXPECT_EQ(player.bank().size(), 4U);
    EXPECT_TRUE(_game.discardPile().empty());
}
