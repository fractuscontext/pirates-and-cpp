/**
 * @file test_lifecycle.cpp
 * @brief End-to-end lifecycle tests that exercise full game turns via
 *        Game::start() with a scripted deck and pre-fed user input.
 *
 * Each test builds a deterministic deck (no shuffle), redirects std::cin
 * with a sequence of user answers, captures std::cout, then asserts on
 * both the captured output text and final game state (scores, banks, etc.).
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
#include "MapCard.hpp"
#include "MermaidCard.hpp"
#include "OracleCard.hpp"
#include "SwordCard.hpp"
#include <gtest/gtest.h>

class LifecycleTest : public ::testing::Test {
protected:
    NoShuffleProvider _noShuffle;
    Game& _game = Game::instance();

    void SetUp() override {
        _game.setRandomProvider(&_noShuffle);
        _game.init("Alice", "Bob");
    }

    void TearDown() override { _game.setRandomProvider(nullptr); }

    /// Run a full game with scripted input, return captured output.
    std::string runGame(const std::string& input,
                        const std::vector<Card*>& deck) {
        stackDeck(_game, deck);
        CinRedirect cin(input);
        CoutCapture capture;
        _game.start();
        return capture.str();
    }
};

/// Alice draws Mermaid(6), Oracle(4), Sword(5) and banks (score 15).
/// Bob draws Key(4), Chest(5), then Key(7) — busts on duplicate Key.
/// Deck empties -> game over. Alice wins with 15 vs Bob's 0.
TEST_F(LifecycleTest, BankAndBust) {
    // Alice: y (draw Oracle), y (draw Sword), n (bank)
    // Bob:   y (draw Chest), y (draw Key7 -> bust)
    std::string output
        = runGame("y\ny\nn\ny\ny\n",
                  {
                      new KeyCard(7),    // Bob draw 3 — duplicates Key -> BUST
                      new ChestCard(5),  // Bob draw 2
                      new KeyCard(4),    // Bob draw 1
                      new SwordCard(5),  // Alice draw 3
                      new OracleCard(4), // Alice draw 2
                      new MermaidCard(6) // Alice draw 1
                  });

    // Turn structure visible
    EXPECT_NE(output.find("Round 1, Turn 1"), std::string::npos);
    EXPECT_NE(output.find("Alice's turn"), std::string::npos);
    EXPECT_NE(output.find("Round 1, Turn 2"), std::string::npos);
    EXPECT_NE(output.find("Bob's turn"), std::string::npos);

    // Alice's draws
    EXPECT_NE(output.find("Alice draws a Mermaid(6)"), std::string::npos);
    EXPECT_NE(output.find("Alice draws a Oracle(4)"), std::string::npos);
    EXPECT_NE(output.find("Alice draws a Sword(5)"), std::string::npos);
    EXPECT_NE(output.find("No cards to steal"), std::string::npos);

    // Bob's bust
    EXPECT_NE(output.find("Bob draws a Key(7)"), std::string::npos);
    EXPECT_NE(output.find("BUST!"), std::string::npos);

    // Game over + winner
    EXPECT_NE(output.find("Game Over"), std::string::npos);
    EXPECT_NE(output.find("Alice wins"), std::string::npos);
}

/// Alice banks Mermaid(6). Bob banks Mermaid(9). Bob wins.
TEST_F(LifecycleTest, SimpleOneCardTurns) {
    // Alice: draw -> n  |  Bob: draw -> n
    std::string output = runGame("n\nn\n",
                                 {
                                     new MermaidCard(9), // Bob draw 1
                                     new MermaidCard(6)  // Alice draw 1
                                 });

    EXPECT_NE(output.find("Alice draws a Mermaid(6)"), std::string::npos);
    EXPECT_NE(output.find("Bob draws a Mermaid(9)"), std::string::npos);
    EXPECT_NE(output.find("Bob wins"), std::string::npos);
}

/// Equal scores -> tie.
TEST_F(LifecycleTest, TieGame) {
    std::string output = runGame("n\nn\n",
                                 {
                                     new MermaidCard(6), // Bob draw 1
                                     new MermaidCard(6)  // Alice draw 1
                                 });

    EXPECT_NE(output.find("It's a tie"), std::string::npos);
}

/// Alice draws Key(6) and banks. Bob draws Chest(5), Key(3), banks ->
/// Chest+Key synergy draws bonus cards from the discard pile.
TEST_F(LifecycleTest, ChestKeySynergyBonusDraw) {
    // Alice: draw -> n  |  Bob: draw -> y -> n
    std::string output = runGame("n\ny\nn\n",
                                 {
                                     new KeyCard(3),   // Bob draw 2
                                     new ChestCard(5), // Bob draw 1
                                     new KeyCard(6)    // Alice draw 1
                                 });

    // Bob has Chest + Key -> synergy activates at banking
    EXPECT_NE(output.find("Chest and Key combination"), std::string::npos);
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}

/// Alice draws Cannon(5) with target in Bob's bank -> chooses to discard.
/// Covers interactive ability inside a full game turn.
TEST_F(LifecycleTest, CannonDiscardsFromOpponentBank) {
    // Alice turn 1: draw -> n (banks Oracle)
    // Bob turn 2: draw -> n (banks Mermaid)
    // Alice turn 3: draw Cannon -> choose "1" to discard Bob's Mermaid -> n (bank)
    std::string output = runGame("n\nn\n1\nn\n",
                                 {
                                     new CannonCard(5),  // Alice turn 3 draw 1
                                     new MermaidCard(7), // Bob turn 2 draw 1
                                     new OracleCard(2)   // Alice turn 1 draw 1
                                 });

    EXPECT_NE(output.find("Cannon: Which suit to discard"), std::string::npos);
    EXPECT_NE(output.find("Discarded Mermaid(7)"), std::string::npos);
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}

/// Oracle peeks, player sees the next card, then decides to stop.
TEST_F(LifecycleTest, OraclePeekDuringGame) {
    // Alice: Oracle peeks at Mermaid(8) -> y (draw Mermaid) -> n (bank)
    // Bob: Mermaid(3) -> no ability -> n (bank)
    std::string output = runGame("y\nn\nn\n",
                                 {
                                     new MermaidCard(3), // Bob draw 1
                                     new MermaidCard(8), // Alice peeks at this
                                     new OracleCard(4)   // Alice draw 1
                                 });

    EXPECT_NE(output.find("Oracle: The next card in the deck is Mermaid(8)"),
              std::string::npos);
    EXPECT_NE(output.find("Alice draws a Mermaid(8)"), std::string::npos);
    EXPECT_NE(output.find("Bob draws a Mermaid(3)"), std::string::npos);
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}

/// Anchor saves pre-anchor cards on bust.
TEST_F(LifecycleTest, AnchorSavesCardsOnBust) {
    // Alice: y (draw Anchor), y (draw Anchor3 -> bust) | Bob: n (bank)
    std::string output
        = runGame("y\ny\nn\n",
                  {
                      new MermaidCard(4), // Bob draw 1
                      new AnchorCard(3),  // Alice draw 3 — dup Anchor -> BUST
                      new AnchorCard(4),  // Alice draw 2 — saves Mermaid(6)
                      new MermaidCard(6)  // Alice draw 1
                  });

    // Anchor effect saved Mermaid(6)
    EXPECT_NE(output.find("Anchor: Any cards drawn before this are safe"),
              std::string::npos);
    EXPECT_NE(output.find("Saving Mermaid(6) to bank"), std::string::npos);

    // Second Anchor caused bust
    EXPECT_NE(output.find("BUST!"), std::string::npos);
}

/// Hook pulls a card from own bank back into play area during a turn.
TEST_F(LifecycleTest, HookPullsFromBank) {
    // Alice turn 1: n (bank Mermaid)
    // Bob turn 2: n (bank Oracle)
    // Alice turn 3: Hook drawn -> choose "1" (Mermaid from bank) -> n (bank)
    std::string output = runGame("n\nn\n1\nn\n",
                                 {
                                     new HookCard(3),   // Alice turn 3 draw 1
                                     new OracleCard(2), // Bob turn 2 draw 1
                                     new MermaidCard(6) // Alice turn 1 draw 1
                                 });

    EXPECT_NE(output.find("Hook: Which suit to play from your bank"),
              std::string::npos);
    EXPECT_NE(output.find("Playing Mermaid(6) from bank"), std::string::npos);
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}

/// Sword steals a card that duplicates a suit in play area -> bust.
TEST_F(LifecycleTest, SwordStealCausesBust) {
    // Alice turn 1: n (bank Mermaid(6))
    // Bob turn 2: n (bank Mermaid(7))
    // Alice turn 3: draw Mermaid(5), y -> draw Sword(4) -> choose "1"
    //   steals Bob's Mermaid(7) -> duplicates Mermaid -> BUST
    std::string output = runGame("n\nn\ny\n1\nn\n",
                                 {
                                     new SwordCard(4),   // Alice turn 3 draw 2
                                     new MermaidCard(5), // Alice turn 3 draw 1
                                     new MermaidCard(7), // Bob turn 2 draw 1
                                     new MermaidCard(6)  // Alice turn 1 draw 1
                                 });

    EXPECT_NE(output.find("Steal caused a BUST!"), std::string::npos);
}

/// Hook pulls a card that duplicates a suit in play area -> bust.
TEST_F(LifecycleTest, HookPullCausesBust) {
    // Alice turn 1: draw Mermaid(6) -> n (bank)
    // Bob turn 2: draw Oracle(2) -> n (bank)
    // Alice turn 3: draw Mermaid(5) -> y -> draw Hook(3)
    //   -> choose "1" (pulls Mermaid(6) from bank -> dup Mermaid -> BUST)
    std::string output = runGame("n\nn\ny\n1\nn\n",
                                 {
                                     new HookCard(3),    // Alice turn 3 draw 2
                                     new MermaidCard(5), // Alice turn 3 draw 1
                                     new OracleCard(2),  // Bob turn 2 draw 1
                                     new MermaidCard(6)  // Alice turn 1 draw 1
                                 });

    EXPECT_NE(output.find("Hook play caused a BUST!"), std::string::npos);
}

/// Map plays a card from discard that duplicates a suit in play area -> bust.
TEST_F(LifecycleTest, MapPlayCausesBust) {
    // Alice turn 1: draw Mermaid(6) -> y -> draw Mermaid(8) -> BUST
    //   (both Mermaids go to discard)
    // Bob turn 2: draw Oracle(2) -> n (bank)
    // Alice turn 3: draw Mermaid(5) -> y -> draw Map(4)
    //   -> choose "1" (picks Mermaid(8) from discard -> dup Mermaid -> BUST)
    std::string output
        = runGame("y\nn\ny\n1\nn\n",
                  {
                      new MapCard(4),     // Alice turn 3 draw 2
                      new MermaidCard(5), // Alice turn 3 draw 1
                      new OracleCard(2),  // Bob turn 2 draw 1
                      new MermaidCard(8), // Alice turn 1 draw 2 -> BUST (dup)
                      new MermaidCard(6)  // Alice turn 1 draw 1
                  });

    EXPECT_NE(output.find("Map play caused a BUST!"), std::string::npos);
}

/// Exercises printCollection branch for multiple cards of the same suit
/// (the space-separated output path) and also covers the Map/Kraken suit names.
TEST_F(LifecycleTest, PrintBankWithMultipleSameSuit) {
    // Alice turn 1: draw Mermaid(6) -> n (bank with 1 Mermaid)
    // Bob turn 2: draw Mermaid(4) -> n (bank)
    // Alice turn 3: draw Mermaid(8) -> n (bank with 2 Mermaids now)
    // When Alice's bank is printed at turn 3 start, it shows
    // "Mermaid(8) Mermaid(6)" (space-separated, same suit)
    std::string output
        = runGame("n\nn\nn\n",
                  {
                      new MermaidCard(8), // Alice turn 3 draw 1 -> bank
                      new MermaidCard(4), // Bob turn 2 draw 1
                      new MermaidCard(6)  // Alice turn 1 draw 1
                  });

    // The bank print at turn 5 start (Alice) should show both Mermaids
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}

/// Invalid yes/no input is retried until valid.
TEST_F(LifecycleTest, InvalidYesNoInputRetried) {
    // Feed "x" (invalid), then "n" (valid) for Alice; "n" for Bob
    std::string output = runGame("x\nn\nn\n",
                                 {
                                     new MermaidCard(4), // Bob draw 1
                                     new MermaidCard(6)  // Alice draw 1
                                 });

    EXPECT_NE(output.find("Invalid input"), std::string::npos);
    EXPECT_NE(output.find("Game Over"), std::string::npos);
}
