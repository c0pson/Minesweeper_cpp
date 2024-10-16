/**
 * @file gui.h
 * @brief Implementation of `GUI` class and related functionalities.
*/

#ifndef GUI_H
#define GUI_H

#include "cell.h"
#include "board.h"

#include <vector>
#include <string>

/**
 * @class GUI
 * @brief A class handling graphical user interface operations such as
 * printing the board to the console and clearing the terminal.
 */

class GUI {
private:
const std::string welcome_message =
R"(
        ,--.!,   __  __ ___ _  _ ___ _____      _____ ___ ___ ___ ___ 
     __/   -*-  |  \/  |_ _| \| | __/ __\ \    / / __| __| _ \ __| _ \
   ,d08b.  '|`  | |\/| || || .` | _|\__ \\ \/\/ /| _|| _||  _/ _||   /
   0088MM       |_|  |_|___|_|\_|___|___/ \_/\_/ |___|___|_| |___|_|_\
   `9MMP'           by Piotr Copek
)";
const std::string end_message = 
R"(
        ,--.!,
     __/   -*-
   ,d08b.  '|`
   0088MM        
   `9MMP'     
)";
public:
    GUI() = default;
    void print_board(const Board& board) const;
    void clear_terminal() const;
    void welcome_screen() const;
    void end_screen() const;
};

#endif // GUI_H
