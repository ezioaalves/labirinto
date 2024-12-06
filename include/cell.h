#include <iostream>

class Cell
{
private:
    int x;
    int y;
    Cell *next;

public:
    Cell(int x = 0, int y = 0);
    bool operator==(Cell *other);

    friend class Stack;
};