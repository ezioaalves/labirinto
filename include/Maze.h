#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>

class Maze
{
private:
    char **maze; // array representing the maze
    int rows, cols;

    const char exitMarker;
    const char entryMarker;
    const char visited;
    const char passage;
    const char wall;

    Cell entryCell;
    Cell exitCell;
    Cell currentCell;

    std::stack<Cell> wayBack;   // Stack to keep track of the current path
    std::stack<Cell> mazeStack; // Stack to keep track of untried neighbors

    void loadMaze(const std::string &filename);
    std::vector<Cell> getNeighbors(const Cell &pos) const;
    void markVisited(const Cell &cell);

public:
    Maze(const std::string &filename,
         char exitMarker_ = 'e',
         char entryMarker_ = 'm',
         char visited_ = '.',
         char passage_ = '0',
         char wall_ = '1');

    ~Maze();

    void clearScreen() const;

    friend std::ostream &operator<<(std::ostream &os, const Maze &m);

    bool exitMaze();

    Cell getEntry() const;
    Cell getExit() const;
};

#endif
