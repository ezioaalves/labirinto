#include <iostream>
#include "stack.h"

class Maze
{
private:
    Cell *currentCell, *exitCell, *entryCell;
    const char exitMarker, entryMarker, visited, passage, wall;
    Stack maze;

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

public:
    void exitMaze();
    Maze(std::pair<int, int> currentCell, std::pair<int, int> exitCell, std::pair<int, int> entryCell);
};