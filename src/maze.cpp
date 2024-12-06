#include "../include/maze.h"

Maze::Maze(std::pair<int, int> currentCell, std::pair<int, int> exitCell, std::pair<int, int> entryCell)
    : currentCell(new Cell(currentCell.first, currentCell.second)),
      exitCell(new Cell(exitCell.first, exitCell.second)),
      entryCell(new Cell(entryCell.first, entryCell.second)),
      exitMarker('e'),
      entryMarker('m'),
      visited('.'),
      passage('0'),
      wall('1')
{
    maze.push(currentCell.first, currentCell.second);
}