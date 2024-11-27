#include <iostream>
#include "cell.h"
#include "stack.h"

class Maze
{
private:
    Cell *currentCell, exitCell, entryCell;
    const char exitMarker, entryMarker, visited, passage, wall;
    Stack maze;

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

public:
    void exitMaze();
    Maze();
};