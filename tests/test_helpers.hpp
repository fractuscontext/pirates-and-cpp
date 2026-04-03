/**
 * @file test_helpers.hpp
 * @brief Shared test utilities: stream redirectors, cout capture/suppression,
 *        no-op shuffle provider, and deck manipulation helpers.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef TEST_HELPERS_HPP
#define TEST_HELPERS_HPP

#include "Card.hpp"
#include "Game.hpp"
#include "RandomProvider.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// No-op shuffle so the deck stays in the order we push.
class NoShuffleProvider : public RandomProvider {
public:
    void shuffle(CardCollection& /*cards*/) override {}
    std::string pickPlayerName() override { return "Test"; }
};

/// RAII redirect of std::cin from a string.
class CinRedirect {
public:
    explicit CinRedirect(const std::string& input)
        : _buf(input), _oldBuf(std::cin.rdbuf(_buf.rdbuf())) {}
    ~CinRedirect() { std::cin.rdbuf(_oldBuf); }
    CinRedirect(const CinRedirect&) = delete;
    CinRedirect& operator=(const CinRedirect&) = delete;
    CinRedirect(CinRedirect&&) = delete;
    CinRedirect& operator=(CinRedirect&&) = delete;

private:
    std::istringstream _buf;
    std::streambuf* _oldBuf;
};

/// RAII capture of std::cout into a retrievable string.
class CoutCapture {
public:
    CoutCapture() : _oldBuf(std::cout.rdbuf(_capture.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(_oldBuf); }
    [[nodiscard]] std::string str() const { return _capture.str(); }
    CoutCapture(const CoutCapture&) = delete;
    CoutCapture& operator=(const CoutCapture&) = delete;
    CoutCapture(CoutCapture&&) = delete;
    CoutCapture& operator=(CoutCapture&&) = delete;

private:
    std::ostringstream _capture;
    std::streambuf* _oldBuf;
};

/// RAII suppressor that discards all std::cout output during its lifetime.
class CoutSuppressor {
public:
    CoutSuppressor() : _oldBuf(std::cout.rdbuf(_null.rdbuf())) {}
    ~CoutSuppressor() { std::cout.rdbuf(_oldBuf); }
    CoutSuppressor(const CoutSuppressor&) = delete;
    CoutSuppressor& operator=(const CoutSuppressor&) = delete;
    CoutSuppressor(CoutSuppressor&&) = delete;
    CoutSuppressor& operator=(CoutSuppressor&&) = delete;

private:
    std::ostringstream _null;
    std::streambuf* _oldBuf;
};

/// Replace the deck with a custom sequence. Cards pushed first are drawn last
/// (deck pops from back). Deletes any cards already in the deck.
inline void stackDeck(Game& game, const std::vector<Card*>& bottomToTop) {
    for(auto* card : game.deck()) {
        delete card;
    }
    game.deck().clear();
    for(auto* card : bottomToTop) {
        game.deck().push_back(card);
    }
}

#endif
