/**
 * @file player.cpp
 * @brief Implementation of `Player` class and related functionalities.
*/

#include <iostream>
#include <limits>
#include <cmath>

#include "player.h"
#include "gui.h"

/**
 * @brief Gets the player's move.
 * 
 * Prompts the player to input the coordinates and the mode of the move.
 * The coordinates are adjusted to zero-based indexing for internal processing.
 * 
 * @param board_x The maximum x-coordinate (width) of the board.
 * @param board_y The maximum y-coordinate (height) of the board.
 * @return A tuple containing the x-coordinate, y-coordinate, and mode of the move.
 * 
 * @details The function asks the player to input the row and column where they
 * want to make a move, as well as the mode of the move (1 to reveal a cell or
 * 2 to mark/un-mark a bomb). It verifies that the inputs are within valid ranges
 * before returning them as a tuple.
 */

std::tuple<int, int, int> Player::player_move(int board_x, int board_y)
{
    int x_cord, y_cord, mode;
    verify_input(x_cord, "Insert row: ", 1, board_y);
    verify_input(y_cord, "Insert column: ", 1, board_x);
    if (first_move) {
        first_move = false;
        return std::make_tuple(x_cord-1, y_cord-1, 1);
    }
    verify_input(mode, "Insert mode [1 - reveal cell | 2 - (un)mark bomb]: ", 1, 2);
    return std::make_tuple(x_cord-1, y_cord-1, mode);
}

/**
 * @brief Verifies and retrieves an input within a specified range.
 * 
 * Prompts the user for input until a valid integer within the specified range is entered.
 * 
 * @param input Reference to the variable where the input will be stored.
 * @param prompt The message displayed to prompt the user for input.
 * @param min The minimum valid value for the input.
 * @param max The maximum valid value for the input.
 * @return true when a valid input has been entered.
 * 
 * @details This function repeatedly prompts the user for input until a valid
 * integer within the specified range is provided. It handles invalid input by
 * clearing the input stream and displaying appropriate error messages.
 */

bool Player::verify_input(int& input, const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            GUI gui;
            gui.clear_terminal();
            continue;
        }
        try {
            size_t pos;
            int temp = std::stoi(line, &pos);
            if (pos == line.length()) {
                if (temp >= min && temp <= max) {
                    input = temp;
                    return true;
                } else {
                    std::cout << "Input out of range. Please enter a number between " << min << " and " << max << "." << std::endl;
                }
            } else {
                std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            }
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        } catch (std::out_of_range& e) {
            std::cout << "Number out of range. Please enter a smaller number." << std::endl;
        }
    }
}

/**
 * @brief Retrieves the dimensions of the game board.
 * 
 * Prompts the player to input the width and height of the game board.
 * 
 * @return A tuple containing the width and height of the board.
 * 
 * @details The function asks the player to input the dimensions of the game board.
 * It verifies that the inputs are within valid ranges (width and height between 5 and 100)
 * before returning them as a tuple.
 */

std::tuple<int, int> Player::get_board_dimensions() {
    int width, height;
    verify_input(width, "Provide width of the board: ", 5, 50);
    verify_input(height, "Provide height of the board: ", 5, 50);
    return std::make_tuple(width, height);
}

/**
 * @brief Retrieves if player wants to play again.
 */

bool Player::play_again() {
    std::string play_again;
    std::cout << "Play again? [y - yes | n - no]: " ;
    std::cin >> play_again;
    while (true) {
        if (play_again == "n") {
            return false;
        }
        if (play_again == "y") {
            return true;
        }
        std::cout << "Provide y or n to continue: ";
        std::cin >> play_again;
    }
}
