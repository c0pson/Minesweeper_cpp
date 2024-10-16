/**
 * @file board.h
 * @brief Class representing board handling game loop.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <tuple>
#include <string>

#include "cell.h"
#include "randomizer.h"

/**
 * @class Board
 * @brief A class holding current state of the game, checks win, loose conditions.
*/

class Board {
private:
    std::vector<std::vector<Cell>> board;
    int width;
    int height;
    int bomb_amount;
    int first_x;
    int first_y;
    RandomNumberGenerator rng;
public:
    Board(int w, int h, int bombs, int x, int y);
    std::vector<std::vector<Cell>> create_board();
    void count_bombs(int x, int y);
    void place_bombs();
    void update_board();
    bool handle_first_mode(Board& board, Cell& cell, int row, int column);
    void reveal_around(int row, int column);
    void handle_second_mode(Cell& cell);
    bool handle_win_condition();
    void handle_lose_condition();
    const std::vector<std::vector<Cell>>& get_board() const;
    Cell& get_cell(int row, int col);
};

#endif //BOARD_H
