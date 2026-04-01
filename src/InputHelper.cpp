/**
 * @file InputHelper.cpp
 * @brief Implements input validation helpers.
 *
 * SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
 * SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
 * SPDX-License-Identifier: MIT
 */
#include "InputHelper.hpp"
#include <iostream>
#include <limits>
#include <utility>

namespace InputHelper {

bool askYesNo(const std::string& prompt) {
    std::string input;
    while(true) {
        std::cout << prompt;
        std::cin >> input;
        if(input == "y" || input == "n") {
            return input == "y";
        }
        std::cout << "Invalid input. Please enter 'y' or 'n'." << '\n';
    }
}

int askChoice(const std::string& prompt, std::size_t count) {
    int choice = 0;
    while(true) {
        std::cout << prompt;
        if(!(std::cin >> choice) || choice < 0
           || std::cmp_greater_equal(choice, count)) {
            std::cout << "Invalid choice. Please enter a number between 0 and "
                      << count - 1 << "." << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return choice;
    }
}

} // namespace InputHelper
