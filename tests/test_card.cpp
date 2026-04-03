/**
 * @file test_card.cpp
 * @brief Unit tests for Card base class and all concrete card subclasses.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */

#include "AnchorCard.hpp"
#include "CannonCard.hpp"
#include "Card.hpp"
#include "ChestCard.hpp"
#include "HookCard.hpp"
#include "KeyCard.hpp"
#include "KrakenCard.hpp"
#include "MapCard.hpp"
#include "MermaidCard.hpp"
#include "OracleCard.hpp"
#include "SwordCard.hpp"
#include <gtest/gtest.h>

TEST(CardTest, CannonCardTypeAndValue) {
    CannonCard card(5);
    EXPECT_EQ(card.type(), CardType::Cannon);
    EXPECT_EQ(card.value(), 5);
}

TEST(CardTest, ChestCardTypeAndValue) {
    ChestCard card(3);
    EXPECT_EQ(card.type(), CardType::Chest);
    EXPECT_EQ(card.value(), 3);
}

TEST(CardTest, KeyCardTypeAndValue) {
    KeyCard card(7);
    EXPECT_EQ(card.type(), CardType::Key);
    EXPECT_EQ(card.value(), 7);
}

TEST(CardTest, SwordCardTypeAndValue) {
    SwordCard card(4);
    EXPECT_EQ(card.type(), CardType::Sword);
    EXPECT_EQ(card.value(), 4);
}

TEST(CardTest, HookCardTypeAndValue) {
    HookCard card(6);
    EXPECT_EQ(card.type(), CardType::Hook);
    EXPECT_EQ(card.value(), 6);
}

TEST(CardTest, OracleCardTypeAndValue) {
    OracleCard card(2);
    EXPECT_EQ(card.type(), CardType::Oracle);
    EXPECT_EQ(card.value(), 2);
}

TEST(CardTest, MapCardTypeAndValue) {
    MapCard card(5);
    EXPECT_EQ(card.type(), CardType::Map);
    EXPECT_EQ(card.value(), 5);
}

TEST(CardTest, MermaidCardTypeAndValue) {
    MermaidCard card(9);
    EXPECT_EQ(card.type(), CardType::Mermaid);
    EXPECT_EQ(card.value(), 9);
}

TEST(CardTest, KrakenCardTypeAndValue) {
    KrakenCard card(3);
    EXPECT_EQ(card.type(), CardType::Kraken);
    EXPECT_EQ(card.value(), 3);
}

TEST(CardTest, AnchorCardTypeAndValue) {
    AnchorCard card(4);
    EXPECT_EQ(card.type(), CardType::Anchor);
    EXPECT_EQ(card.value(), 4);
}

TEST(CardTest, CannonStr) {
    CannonCard card(7);
    EXPECT_EQ(card.str(), "Cannon(7)");
}

TEST(CardTest, ChestStr) {
    ChestCard card(2);
    EXPECT_EQ(card.str(), "Chest(2)");
}

TEST(CardTest, KeyStr) {
    KeyCard card(4);
    EXPECT_EQ(card.str(), "Key(4)");
}

TEST(CardTest, SwordStr) {
    SwordCard card(6);
    EXPECT_EQ(card.str(), "Sword(6)");
}

TEST(CardTest, HookStr) {
    HookCard card(3);
    EXPECT_EQ(card.str(), "Hook(3)");
}

TEST(CardTest, OracleStr) {
    OracleCard card(5);
    EXPECT_EQ(card.str(), "Oracle(5)");
}

TEST(CardTest, MapStr) {
    MapCard card(2);
    EXPECT_EQ(card.str(), "Map(2)");
}

TEST(CardTest, MermaidStr) {
    MermaidCard card(8);
    EXPECT_EQ(card.str(), "Mermaid(8)");
}

TEST(CardTest, KrakenStr) {
    KrakenCard card(6);
    EXPECT_EQ(card.str(), "Kraken(6)");
}

TEST(CardTest, AnchorStr) {
    AnchorCard card(5);
    EXPECT_EQ(card.str(), "Anchor(5)");
}

TEST(CardTest, StandardSuitMinValue) {
    CannonCard card(2);
    EXPECT_EQ(card.value(), 2);
    EXPECT_EQ(card.str(), "Cannon(2)");
}

TEST(CardTest, StandardSuitMaxValue) {
    CannonCard card(7);
    EXPECT_EQ(card.value(), 7);
    EXPECT_EQ(card.str(), "Cannon(7)");
}

TEST(CardTest, MermaidMinValue) {
    MermaidCard card(4);
    EXPECT_EQ(card.value(), 4);
    EXPECT_EQ(card.str(), "Mermaid(4)");
}

TEST(CardTest, MermaidMaxValue) {
    MermaidCard card(9);
    EXPECT_EQ(card.value(), 9);
    EXPECT_EQ(card.str(), "Mermaid(9)");
}

TEST(CardTest, DifferentCardsDifferentTypes) {
    CannonCard cannon(5);
    ChestCard chest(5);
    EXPECT_NE(cannon.type(), chest.type());
}

TEST(CardTest, SameTypeDifferentValues) {
    CannonCard card1(2);
    CannonCard card2(7);
    EXPECT_EQ(card1.type(), card2.type());
    EXPECT_NE(card1.value(), card2.value());
}
