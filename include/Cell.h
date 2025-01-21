#ifndef CELL_H
#define CELL_H
#include <iostream>

class Cell
{

private:
    int row;
    int col;

public:
    Cell(int r = -1, int c = -1);

    bool operator==(const Cell &other) const;
    friend class Maze;

    int getRow() const { return row; }
    int getCol() const { return col; }
};

#endif
