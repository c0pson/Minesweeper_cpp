/**
 * @file player.h
 * @brief Class handling player interactions with terminal.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <tuple>
#include <string>

/**
 * @class `Player`
 * @brief A class holding user interactions with the game functionalities.
*/

class Player {
private:
    bool first_move = true;
public:
    std::tuple<int, int, int> player_move(int board_x, int board_y);
    bool verify_input(int& input, const std::string& prompt, int min, int max);
    std::tuple<int, int> get_board_dimensions();
    bool play_again();
};

#endif //PLAYER_H
