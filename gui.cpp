/**
 * @file gui.cpp
 * @brief Implementation of `GUI` class and related functionalities.
*/

#include "GUI.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

/**
 * @brief Prints the board matrix to the console.
 *
 * This method retrieves the matrix from the Board object and prints each
 * cell to the console, arranging them in rows and columns.
 *
 * @param board The Board object containing the matrix to be printed.
 */

void GUI::print_board(const Board& board) const {
    const std::vector<std::vector<Cell>>& matrix = board.get_board();
    int col_amount = matrix.empty() ? 0 : matrix[0].size();
    std::cout << " 💣 ┃"; //hope the emoji will not break
    for (int i=1; i<=col_amount; i++) {
        std::cout << std::setw(2) << i;
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "━━━━╋";
    for (int i=1; i<=col_amount; i++) {
        std::cout << "━━━";
    }
    std::cout << "┓" << std::endl;
    int row_index = 1;
    for (const auto& row : matrix) {
        std::cout << std::setw(3) << row_index << " ┃";
        for (const auto& element : row) {
            std::cout << " " << element << " ";
        }
        std::cout << "┃" <<  std::endl;
        row_index++;
    }
    std::cout << "━━━━┻";
    for (int i=1; i<=col_amount; i++) {
        std::cout << "━━━";
    }
    std::cout << "┛" << std::endl;
}

/**
 * @brief Clears the terminal screen.
 *
 * This method uses system-specific commands to clear the terminal.
 * On Windows, it uses the "cls" command. Otherwise it uses
 * the "clear" command.
 */

void GUI::clear_terminal() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void GUI::welcome_screen() const {
    clear_terminal();
    std::cout << welcome_message << std::endl;
}

void GUI::end_screen() const {
    clear_terminal();
    std::cout << end_message << std::endl;
}
