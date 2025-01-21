#include "Cell.h"

Cell::Cell(int r, int c) : row(r), col(c) {}

bool Cell::operator==(const Cell &other) const
{
    return row == other.row && col == other.col;
}
