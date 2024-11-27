#include <iostream>

class Cell
{
private:
    int x;
    int y;
    Cell *next;

public:
    Cell(int x, int y);
    bool operator==(Cell *other);

    friend class Stack;
};