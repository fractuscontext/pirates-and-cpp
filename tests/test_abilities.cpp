/**
 * @file test_abilities.cpp
 * @brief Unit tests for individual card abilities (Oracle, Mermaid, Chest, Key,
 *        Anchor, Kraken, Cannon, Sword, Hook, Map).
 *
 * Abilities that require interactive input (Cannon, Sword, Hook, Map) are
 * tested by feeding std::cin via istringstream. This allows full coverage
 * without manual interaction.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "test_helpers.hpp"

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
#include <gtest/gtest.h>
#include <vector>

class AbilityTest : public ::testing::Test {
protected:
    Game& _game = Game::instance();
    Player* _player = nullptr;
    Player* _opponent = nullptr;

    void SetUp() override {
        _game.init();
        _player = &_game.currentPlayer();
        _opponent = &_game.otherPlayer();
    }
};

TEST_F(AbilityTest, OraclePeeksTopOfDeck) {
    Card* const expectedTop = _game.topDeck();
    ASSERT_NE(expectedTop, nullptr);

    size_t const sizeBefore = _game.deck().size();
    OracleCard oracle(5);
    {
        CoutSuppressor suppress;
        oracle.play(_game, *_player);
    }
    EXPECT_EQ(_game.deck().size(), sizeBefore);
    EXPECT_EQ(_game.topDeck(), expectedTop);
}

TEST_F(AbilityTest, OracleEmptyDeckDoesNotCrash) {
    _game.deck().clear();

    OracleCard oracle(3);
    {
        CoutSuppressor suppress;
        EXPECT_NO_THROW(oracle.play(_game, *_player));
    }
}

TEST_F(AbilityTest, MermaidHasNoEffect) {
    size_t const deckSize = _game.deck().size();
    size_t const discardSize = _game.discardPile().size();

    MermaidCard mermaid(7);
    {
        CoutSuppressor suppress;
        mermaid.play(_game, *_player);
    }

    EXPECT_EQ(_game.deck().size(), deckSize);
    EXPECT_EQ(_game.discardPile().size(), discardSize);
}

TEST_F(AbilityTest, ChestHasNoImmediateEffect) {
    size_t const deckSize = _game.deck().size();
    size_t const discardSize = _game.discardPile().size();

    ChestCard chest(4);
    {
        CoutSuppressor suppress;
        chest.play(_game, *_player);
    }

    EXPECT_EQ(_game.deck().size(), deckSize);
    EXPECT_EQ(_game.discardPile().size(), discardSize);
}

TEST_F(AbilityTest, KeyHasNoImmediateEffect) {
    size_t const deckSize = _game.deck().size();
    size_t const discardSize = _game.discardPile().size();

    KeyCard key(6);
    {
        CoutSuppressor suppress;
        key.play(_game, *_player);
    }

    EXPECT_EQ(_game.deck().size(), deckSize);
    EXPECT_EQ(_game.discardPile().size(), discardSize);
}

TEST_F(AbilityTest, CannonDiscardsFromOpponentBank) {
    _opponent->bank().push_back(new MermaidCard(8));
    EXPECT_EQ(_opponent->bank().size(), 1U);

    CannonCard cannon(5);
    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        cannon.play(_game, *_player);
    }

    EXPECT_TRUE(_opponent->bank().empty());
    EXPECT_EQ(_game.discardPile().size(), 1U);
}

TEST_F(AbilityTest, CannonEmptyOpponentBankNoEffect) {
    EXPECT_TRUE(_opponent->bank().empty());

    CannonCard cannon(3);
    {
        CoutSuppressor suppress;
        cannon.play(_game, *_player);
    }

    EXPECT_TRUE(_opponent->bank().empty());
    EXPECT_TRUE(_game.discardPile().empty());
}

TEST_F(AbilityTest, CannonDiscardsHighestValueOfChosenSuit) {
    _opponent->bank().push_back(new MermaidCard(5));
    _opponent->bank().push_back(new MermaidCard(9));

    CannonCard cannon(4);
    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        cannon.play(_game, *_player);
    }

    EXPECT_EQ(_opponent->bank().size(), 1U);
    EXPECT_EQ(_opponent->bank()[0]->value(), 5);
    EXPECT_EQ(_game.discardPile().size(), 1U);
    EXPECT_EQ(_game.discardPile()[0]->value(), 9);
}

TEST_F(AbilityTest, SwordStealsFromOpponentBank) {
    _opponent->bank().push_back(new MermaidCard(7));

    SwordCard sword(4);
    _player->playArea().push_back(&sword);

    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        sword.play(_game, *_player);
    }

    EXPECT_TRUE(_opponent->bank().empty());
    EXPECT_GE(_player->playArea().size(), 2U);

    std::erase(_player->playArea(), &sword);
}

TEST_F(AbilityTest, SwordEmptyOpponentBankNoEffect) {
    SwordCard sword(5);
    {
        CoutSuppressor suppress;
        sword.play(_game, *_player);
    }

    EXPECT_TRUE(_player->playArea().empty());
}

TEST_F(AbilityTest, HookPullsFromOwnBank) {
    _player->bank().push_back(new MermaidCard(6));

    HookCard hook(3);
    _player->playArea().push_back(&hook);

    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        hook.play(_game, *_player);
    }

    EXPECT_TRUE(_player->bank().empty());
    EXPECT_GE(_player->playArea().size(), 2U);

    std::erase(_player->playArea(), &hook);
}

TEST_F(AbilityTest, HookEmptyBankNoEffect) {
    HookCard hook(4);
    {
        CoutSuppressor suppress;
        hook.play(_game, *_player);
    }

    EXPECT_TRUE(_player->playArea().empty());
}

TEST_F(AbilityTest, MapDrawsFromDiscardPile) {
    _game.discardCard(new MermaidCard(4));
    _game.discardCard(new CannonCard(3));
    _game.discardCard(new KeyCard(5));

    MapCard map(2);
    _player->playArea().push_back(&map);

    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        map.play(_game, *_player);
    }

    EXPECT_GE(_player->playArea().size(), 2U);
    EXPECT_EQ(_game.discardPile().size(), 2U);

    std::erase(_player->playArea(), &map);
}

TEST_F(AbilityTest, MapEmptyDiscardNoEffect) {
    EXPECT_TRUE(_game.discardPile().empty());

    MapCard map(3);
    {
        CoutSuppressor suppress;
        map.play(_game, *_player);
    }

    EXPECT_TRUE(_player->playArea().empty());
}

TEST_F(AbilityTest, MapFewerThan3InDiscard) {
    _game.discardCard(new MermaidCard(8));

    MapCard map(2);
    _player->playArea().push_back(&map);

    {
        CinRedirect redirect("1\n");
        CoutSuppressor suppress;
        map.play(_game, *_player);
    }

    EXPECT_GE(_player->playArea().size(), 2U);
    EXPECT_TRUE(_game.discardPile().empty());

    std::erase(_player->playArea(), &map);
}

TEST_F(AbilityTest, KrakenForces3Draws) {
    size_t const deckBefore = _game.deck().size();
    KrakenCard kraken(5);

    {
        CoutSuppressor suppress;
        kraken.play(_game, *_player);
    }

    size_t const cardsDrawn = deckBefore - _game.deck().size();
    EXPECT_GE(cardsDrawn, 1U);
}

TEST_F(AbilityTest, KrakenStopsOnBust) {
    auto* seeded = new MermaidCard(4);
    {
        CoutSuppressor suppress;
        _player->playCard(seeded, _game);
    }

    auto savedDeck = std::move(_game.deck());
    _game.deck().clear();
    _game.deck().push_back(new MermaidCard(9));

    KrakenCard kraken(2);
    {
        CoutSuppressor suppress;
        kraken.play(_game, *_player);
    }

    EXPECT_TRUE(_player->isBust());

    for(auto* card : savedDeck) {
        _game.deck().push_back(card);
    }
}

TEST_F(AbilityTest, KrakenEmptyDeckDrawsNothing) {
    auto savedDeck = std::move(_game.deck());
    _game.deck().clear();

    size_t const playAreaBefore = _player->playArea().size();
    KrakenCard kraken(3);
    {
        CoutSuppressor suppress;
        kraken.play(_game, *_player);
    }

    EXPECT_EQ(_player->playArea().size(), playAreaBefore);

    _game.deck() = std::move(savedDeck);
}

TEST_F(AbilityTest, AnchorSavesPreAnchorCardsToBank) {
    auto* priorCard = new MermaidCard(6);
    _player->playArea().push_back(priorCard);

    auto* anchor = new AnchorCard(4);
    _player->playArea().push_back(anchor);

    {
        CoutSuppressor suppress;
        anchor->play(_game, *_player);
    }

    EXPECT_EQ(_player->bank().size(), 1U);
    EXPECT_EQ(_player->bank()[0]->str(), "Mermaid(6)");

    EXPECT_EQ(_player->playArea().size(), 1U);
    EXPECT_EQ(_player->playArea()[0]->str(), "Anchor(4)");
}

TEST_F(AbilityTest, AnchorNoPreCardsNothingMoved) {
    auto* anchor = new AnchorCard(5);
    _player->playArea().push_back(anchor);

    {
        CoutSuppressor suppress;
        anchor->play(_game, *_player);
    }

    EXPECT_TRUE(_player->bank().empty());
    EXPECT_EQ(_player->playArea().size(), 1U);
}

TEST_F(AbilityTest, AnchorSavesMultiplePreCards) {
    _player->playArea().push_back(new MermaidCard(5));
    _player->playArea().push_back(new CannonCard(3));
    _player->playArea().push_back(new KeyCard(7));

    auto* anchor = new AnchorCard(2);
    _player->playArea().push_back(anchor);

    {
        CoutSuppressor suppress;
        anchor->play(_game, *_player);
    }

    EXPECT_EQ(_player->bank().size(), 3U);
    EXPECT_EQ(_player->playArea().size(), 1U);
    EXPECT_EQ(_player->playArea()[0], anchor);
}

//--- InputHelper edge cases ---

TEST_F(AbilityTest, CannonRecoversFromInvalidChoice) {
    //Feed invalid input "0" then valid "1" to cover the error path
    _opponent->bank().push_back(new MermaidCard(7));

    CannonCard cannon(5);
    {
        CinRedirect redirect("0\n1\n");
        CoutSuppressor suppress;
        cannon.play(_game, *_player);
    }

    EXPECT_TRUE(_opponent->bank().empty());
    EXPECT_EQ(_game.discardPile().size(), 1U);
}

TEST_F(AbilityTest, CannonRecoversFromNonNumericChoice) {
    //Feed "abc" then "1" to cover cin.clear()/ignore path
    _opponent->bank().push_back(new MermaidCard(7));

    CannonCard cannon(5);
    {
        CinRedirect redirect("abc\n1\n");
        CoutSuppressor suppress;
        cannon.play(_game, *_player);
    }

    EXPECT_TRUE(_opponent->bank().empty());
    EXPECT_EQ(_game.discardPile().size(), 1U);
}
