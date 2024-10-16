/**
 * @file board.cpp
 * @brief Implementation of `Board` class and related functionalities.
 */

#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <tuple>

#include "randomizer.h"
#include "board.h"
#include "cell.h"

/**
 * @brief Constructs a new Board object.
 * 
 * Initializes the board with given dimensions, number of bombs, and the first cell's coordinates.
 * 
 * @param w Width of the board.
 * @param h Height of the board.
 * @param bombs Number of bombs to place on the board.
 * @param x X-coordinate of the first cell.
 * @param y Y-coordinate of the first cell.
 */

Board::Board(int w, int h, int bombs, int x, int y) : width(w), height(h), bomb_amount(bombs), first_x(x), first_y(y) {
    board = create_board();
};

/**
 * @brief Creates a new board with default cells.
 * 
 * Initializes a 2D vector of cells with default values.
 * 
 * @return A 2D vector representing the board.
 */

std::vector<std::vector<Cell>> Board::create_board() {
    std::vector<std::vector<Cell>> new_board(height, std::vector<Cell>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            new_board[i][j] = Cell();
        }
    }
    return new_board;
}

/**
 * @brief Counts the number of bombs around a specific cell.
 * 
 * Updates the bomb counter for the cell at given coordinates x and y.
 * 
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 */

void Board::count_bombs(int x, int y) {
    std::tuple<int, int> original_tuple = std::make_tuple (x, y);
    for (int i = std::max(0, x-1); i < std::min(height, x+2); i++) {
        for (int j = std::max(0, y - 1); j < std::min(width, y + 2); ++j) {
            if (board[i][j].get_is_bomb() && std::make_tuple(i, j) != original_tuple) {
                board[x][y].update_counter();
            }
        }
    }
}

/**
 * @brief Places bombs randomly on the board.
 * 
 * Ensures that bombs are not placed on or around the first cell chosen by the player.
 */

void Board::place_bombs() {
    int changed = 0;
    std::vector<std::tuple<int, int>> already_changed;
    std::vector<std::tuple<int, int>> offsets = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},  {0, 0},  {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };
    for (const auto& offset : offsets) {
        already_changed.emplace_back(first_x + std::get<0>(offset), first_y + std::get<1>(offset));
    }
    while (changed < bomb_amount) {
        int row = rng.get_random_number(0, height - 1);
        int column = rng.get_random_number(0, width - 1);
        if (std::find(already_changed.begin(), already_changed.end(), std::make_tuple(row, column)) == already_changed.end()) {
            already_changed.push_back({row, column});
            board[row][column] = MineCell();
            changed++;
        }
    }
}

/**
 * @brief Handles the first mode of cell interaction.
 * 
 * Reveals a cell and its surroundings if it is not a bomb or marked. Ends the game if a bomb is revealed.
 * 
 * @param board Reference to the board.
 * @param cell Reference to the cell user interacts with.
 * @param row Row of the cell.
 * @param column Column of the cell.
 * 
 * @return True if the game continues, false if the game is lost.
 */

bool Board::handle_first_mode(Board& board, Cell& cell, int row, int column) {
    if (cell.get_is_marked()) {
        cell.flag_bomb();
    }
    if (!cell.get_is_revealed() && !cell.get_is_bomb()) {
        cell.reveal();
        board.reveal_around(row, column);
        if (cell.get_is_marked()) {
        }
    } else if (cell.get_is_bomb()) {
        handle_lose_condition();
        return false;
    }
    return true;
}

/**
 * @brief Handles the second mode of cell interaction.
 * 
 * Flags a cell as a bomb if it is not flagged yet.
 * 
 * @param cell Reference to the cell being interacted with.
 */

void Board::handle_second_mode(Cell& cell) {
    if (!cell.get_is_revealed()) {
        cell.flag_bomb();
    }
}

/**
 * @brief Reveals the cells around a specified cell.
 * 
 * Recursively reveals cells if they do not have bombs around them.
 * 
 * @param row Row of the cell.
 * @param column Column of the cell.
 */

void  Board::reveal_around(int row, int column) {
    if (board[row][column].get_bombs_around()) {
        return;
    }
    for (int i = std::max(0, row - 1); i < std::min(row + 2, height); ++i) {
        for (int j = std::max(0, column - 1); j < std::min(column + 2, width); ++j) {
            if (!board[i][j].get_is_revealed() && !board[i][j].get_is_bomb()) {
                board[i][j].reveal();
                if (board[i][j].get_bombs_around() == 0 && !board[i][j].get_is_bomb()) {
                    reveal_around(i, j);
                }
            }
        }
    }
}

/**
 * @brief Gets the board.
 * 
 * @return A constant reference to the 2D vector representing the board.
 */

const std::vector<std::vector<Cell>>& Board::get_board() const {
    return board;
}

/**
 * @brief Gets a cell from the board.
 * 
 * @param row Row of the cell.
 * @param col Column of the cell.
 * 
 * @return Reference to the cell at the specified position.
 */

Cell& Board::get_cell(int row, int col) {
    return board[row][col];
}

/**
 * @brief Checks if the win condition is met.
 * 
 * @return True if there are still cells to be revealed or bombs to be marked, false if the game is won.
 */

bool Board::handle_win_condition() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (!cell.get_is_revealed() && !cell.get_is_bomb()) {
                return true;
            }
            if (cell.get_is_bomb() && !cell.get_is_marked()) {
                return true;
            }
        }
    }
    std::cout << "You won the game!!!" << std::endl;
    return false;
}

/**
 * @brief Handles the lose condition.
 * 
 * Reveals all cells on the board when the game is lost.
 */

void Board::handle_lose_condition() {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell.reveal();
        }
    }
}
