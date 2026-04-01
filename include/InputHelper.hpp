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
 * @brief Prompts for an integer in [0, count) until a valid response is given.
 *
 * @param prompt The prompt text to display.
 * @param count  The number of valid options (0 .. count-1).
 * @return The validated choice.
 */
int askChoice(const std::string& prompt, std::size_t count);

} // namespace InputHelper

#endif
