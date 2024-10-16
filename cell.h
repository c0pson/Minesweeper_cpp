/**
 * @file cell.h
 * @brief Classes representing cells in a board game, including empty cells and mine cells.
 */

#ifndef CELL_H
#define CELL_H

#include <ostream>

/**
 * @class Cell
 * @brief A class representing a generic cell on the board.
 */

class Cell {
private:
    bool is_bomb;
    bool is_marked;
    bool is_revealed;
    int bombs_around;
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
public:
    Cell();
    virtual ~Cell() = default;
    bool get_is_bomb() const;
    bool get_is_marked() const;
    bool get_is_revealed() const;
    int get_bombs_around() const;
    void mark_as_bomb();
    void flag_bomb();
    void reveal();
    void update_counter();
    virtual void display(std::ostream& os) const;
    virtual bool is_empty() const { return false; }
    virtual bool is_mine() const { return false; }
};

/**
 * @class EmptyCell
 * @brief A class representing an empty cell on the board.
 */

class EmptyCell : public Cell {
public:
    EmptyCell();
    void display(std::ostream& os) const override;
    bool is_empty() const override { return true; }
};

/**
 * @class MineCell
 * @brief A class representing a mine cell on the board.
 */

class MineCell : public Cell {
public:
    MineCell();
    void display(std::ostream& os) const override;
    bool is_mine() const override { return true; }
};

#endif //CELL_H
