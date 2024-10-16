/**
 * @file gui.cpp
 * @brief Implementation of `Cell` class and related functionalities.
*/

#include <iostream>

#include "cell.h"

/**
 * @brief Overloaded output stream operator for Cell.
 * 
 * This function calls the `display` method of the cell to output its representation.
 * 
 * @param os The output stream.
 * @param cell The cell to output.
 * @return The output stream.
 */

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    cell.display(os);
    return os;
}

/**
 * @brief Constructs a new Cell object.
 * 
 * The Cell is initialized with default values:
 * - `is_bomb`: false
 * - `is_marked`: false
 * - `is_revealed`: false
 * - `bombs_around`: 0
*/
Cell::Cell() {
    is_bomb = false;
    is_marked = false;
    is_revealed = false;
    bombs_around = 0;
}

/**
 * @brief Function used to toggle if cell is a bomb during generation of the board. 
*/
void Cell::mark_as_bomb() {
    is_bomb = true;
}

/**
 * @brief Function used to toggle if cell is marked as a bomb by the player.
*/
void Cell::flag_bomb() {
    is_marked = !is_marked;
}

void Cell::reveal() {
/**
 * @brief Function used to toggle if cell was revealed by player.
*/
    is_revealed = true;
}

/**
 * @brief Increments an amount of bombs around the current cell.
*/
void Cell::update_counter() {
    bombs_around++;
}

/**
 * @brief Checks if the cell is a bomb.
 * 
 * @return true if the cell is a bomb, false otherwise.
 */
bool Cell::get_is_bomb() const {
    return is_bomb;
}

/**
 * @brief Checks if the cell is marked as a potential bomb.
 * 
 * @return true if the cell is marked, false otherwise.
 */
bool Cell::get_is_marked() const {
    return is_marked;
}

bool Cell::get_is_revealed() const {
/**
 * @brief Checks if the cell is revealed by the player.
 * 
 * @return true if the cell is revealed, false otherwise.
 */
    return is_revealed;
}

/**
 * @brief Gets the number of bombs around the cell.
 * 
 * @return The number of bombs around the cell.
 */
int Cell::get_bombs_around() const {
    return bombs_around;
}

void Cell::display(std::ostream& os) const {
    if (is_marked) {
        os << "⚐";
    } else if (!is_revealed) {
        os << "■";
    } else if (is_bomb) {
        os << "⚹";
    } else if (bombs_around) {
        os << bombs_around;
    } else {
        os << " ";
    }
}

/**
 * @brief Constructs a new EmptyCell object.
 * 
 * Initializes an empty cell with default values.
 */

EmptyCell::EmptyCell() : Cell() {}

/**
 * @brief Displays the empty cell using the given output stream.
 * 
 * This method outputs a representation of the empty cell based on its state:
 * - 'F' if the cell is marked by the player.
 * - '.' if the cell is not revealed.
 * - The number of bombs around the cell if it is revealed.
 * 
 * @param os The output stream.
 */

void EmptyCell::display(std::ostream& os) const {
    if (get_is_marked()) {
        os << "⚐";
    } else if (!get_is_revealed()) {
        os << "■";
    } else {
        os << get_bombs_around();
    }
}

/**
 * @brief Constructs a new MineCell object.
 * 
 * Initializes a mine cell and marks it as containing a bomb.
 */

MineCell::MineCell() {
    mark_as_bomb();
}

/**
 * @brief Displays the mine cell using the given output stream.
 * 
 * This method outputs a representation of the mine cell based on its state:
 * - 'F' if the cell is marked by the player.
 * - '.' if the cell is not revealed.
 * - '*' if the cell is revealed and contains a bomb.
 * 
 * @param os The output stream.
 */

void MineCell::display(std::ostream& os) const {
    if (get_is_marked()) {
        os << "⚐";
    } else if (!get_is_revealed()) {
        os << "■";
    } else {
        os << "⚹";
    }
}
