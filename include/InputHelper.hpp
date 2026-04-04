/**
 * @file InputHelper.hpp
 * @brief Input validation helpers for user prompts.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef INPUT_HELPER_HPP
#define INPUT_HELPER_HPP

#include <cstddef>
#include <string>

namespace InputHelper {

/**
 * @brief Prompts for "y" or "n" until a valid response is given.
 *
 * @param prompt The prompt text to display.
 * @return true if the user entered "y", false if "n".
 */
bool askYesNo(const std::string& prompt);

/**
 * @brief Prompts for an integer in [1, count] until a valid response is given.
 *
 * @param prompt The prompt text to display.
 * @param count  The number of valid options (user enters 1 .. count).
 * @return The validated choice as a 0-based index (0 .. count-1).
 */
int askChoice(const std::string& prompt, std::size_t count);

} // namespace InputHelper

#endif
