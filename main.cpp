#include "include/Maze.h"
#include "include/GUI.h"
#include <string>

int main()
{
    std::string filename = "maze2.txt";

    Maze maze(filename);

    GUI gui(maze);
    gui.run();

    return 0;
}
