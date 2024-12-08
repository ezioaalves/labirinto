#include <iostream>
#include "stack.h"

class Maze
{
private:
    Cell *currentCell, *exitCell, *entryCell;
    const char exitMarker = 'e', entryMarker = 'm', visited = '.', passage = '0', wall = '1';
    Stack maze;

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

public:
    void exitMaze();
    Maze(int cont, std::string fileName);
};