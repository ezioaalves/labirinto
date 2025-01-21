#include "Maze.h"
#include <string>

int main()
{
    std::string filename = "maze.txt";

    Maze maze(filename);

    bool found = maze.exitMaze();

    return 0;
}
