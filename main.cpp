/**
 * @file main.cpp
 * @author Piotr Copek
 * @version 1.0
 * @brief Implementation of working minesweeper game.
*/

#include <iostream>

#include "player.h"
#include "gui.h"
#include "board.h"

/**
 * @brief Main game loop for Minesweeper.
 * 
 * @details This function initializes the game, sets up the board, and enters the main game loop where user interactions
 * are handled. The game loop continues until the user hits a bomb or wins the game. The following classes are used:
 *  - `Player` for handling user inputs and moves.
 *  - `Board` for maintaining the state of the game and checking win/loss conditions.
 *  - `GUI` for displaying the board and clearing the terminal.
 */

void game_loop() {
// setup for a game to run
    bool running = true;
    Player player;
    GUI gui;
    int row, column, mode;
    int size_x;
    int size_y;
// board setup
    std::tie(size_x, size_y) = player.get_board_dimensions();
    gui.clear_terminal();
// visualization of a board
    Board representation(size_x, size_y, 0, 0, 0);
    gui.print_board(representation);
// board setup
    int bomb_amount = std::floor((size_x * size_y) * 0.2);
    std::tie(row, column, mode) = player.player_move(size_x, size_y);
    Board board(size_x, size_y, bomb_amount, row, column);
    board.create_board();
    board.place_bombs();
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            board.count_bombs(i, j);
        }
    }
    board.handle_first_mode(board, board.get_cell(row, column), row, column);
    gui.clear_terminal();
    gui.print_board(board);
// mainloop
    while (running) {
        std::tie(row, column, mode) = player.player_move(size_x, size_y);
        switch (mode) {
            case 1:
                running = board.handle_first_mode(board, board.get_cell(row, column), row, column);
                break;
            case 2:
                board.handle_second_mode(board.get_cell(row, column));
                break;
            default:
                break;
        }
        gui.clear_terminal();
        gui.print_board(board);
        if (!running) {
            std::cout << "It was a bomb :c" << std::endl;
        } else {
            running = board.handle_win_condition();
        }
    }
}

/**
 * @brief Main function of the project.
 * 
 * @details The main function initializes the game and handles the welcome screen and game loop.
 * The game loop continues until the user decides to end game.
 * 
 * The following classes are implemented in the game:
 *  - `Player` for handling user interactions.
 *  - `Board` for maintaining the state of the game.
 *  - `GUI` for displaying the game board and messages.
 * 
 * @return int Returns 0 on success.
 */

int main() {
    Player player;
    GUI gui;
    gui.welcome_screen();
    game_loop();
    while (true) {
        if (player.play_again()) {
            game_loop();
        } else {
            break;
        }
    }
    gui.end_screen();
    return 0;
}
