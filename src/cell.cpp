#include "../include/cell.h"

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
    this->next = nullptr;
}

bool Cell::operator==(Cell *other)
{
    if (this->x == other->x && this->y == other->y)
    {
        return true;
    }
    return false;
}