#include "Maze.h"
#include <fstream>
#include <vector>
#include <cstdlib> // For exit()
#include <thread>
#include <chrono>

// ---------------------------------------------------------------------
// Constructor: Initializes the maze by loading it from a file and
// initializing marker attributes.
// ---------------------------------------------------------------------
Maze::Maze(const std::string &filename,
           char exitMarker_,
           char entryMarker_,
           char visited_,
           char passage_,
           char wall_)
    : maze(nullptr),
      rows(0),
      cols(0),
      exitMarker(exitMarker_),
      entryMarker(entryMarker_),
      visited(visited_),
      passage(passage_),
      wall(wall_),
      entryCell(),
      exitCell(),
      currentCell()
{
    loadMaze(filename);
}

Maze::~Maze()
{
    if (maze != nullptr)
    {
        for (int i = 0; i < rows + 2; i++)
        {
            delete[] maze[i];
        }
        delete[] maze;
    }
}

void Maze::clearScreen() const
{
    std::cout << "\033[2J\033[1;1H";
}

// ---------------------------------------------------------------------
// loadMaze: Reads a maze from a file. Format:
//   First line: rows cols
//   Next 'rows' lines: each of exactly 'cols' characters
// Puts a frame of 'wall' characters around the edges, so total size is
// (rows+2)*(cols+2).
// Finds 'entryMarker' => entryCell, 'exitMarker' => exitCell.
// ---------------------------------------------------------------------
void Maze::loadMaze(const std::string &filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        std::cerr << "Error: cannot open " << filename << "\n";
        exit(1);
    }
    infile >> rows >> cols;
    infile.ignore(); // Consume the newline after the dimensions

    // Read the next 'rows' lines
    std::vector<std::string> lines(rows);
    for (int i = 0; i < rows; i++)
    {
        std::getline(infile, lines[i]);
        if (static_cast<int>(lines[i].size()) != cols)
        {
            std::cerr << "Error: line " << i + 1
                      << " has length " << lines[i].size()
                      << ", expected " << cols << "\n";
            exit(1);
        }
    }
    infile.close();

    // Allocate memory for the maze with a frame of 'wall' characters
    maze = new char *[rows + 2];
    for (int r = 0; r < rows + 2; r++)
    {
        maze[r] = new char[cols + 2];
        for (int c = 0; c < cols + 2; c++)
        {
            maze[r][c] = wall; // Initialize frame with walls
        }
    }

    // Copy the input lines into the maze, offset by 1 because of the frame
    bool foundEntry = false, foundExit = false;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            char cellChar = lines[r][c];
            maze[r + 1][c + 1] = cellChar;

            if (cellChar == entryMarker)
            {
                entryCell = Cell(r + 1, c + 1);
                currentCell = entryCell;
                foundEntry = true;
            }
            if (cellChar == exitMarker)
            {
                exitCell = Cell(r + 1, c + 1);
                foundExit = true;
            }
        }
    }

    if (!foundEntry)
    {
        std::cerr << "Error: no '" << entryMarker << "' (entry) found in the maze.\n";
        exit(1);
    }
    if (!foundExit)
    {
        std::cerr << "Error: no '" << exitMarker << "' (exit) found in the maze.\n";
        exit(1);
    }
}

// ---------------------------------------------------------------------
// Overloaded << operator to print the maze with the current mouse position
// ---------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Maze &m)
{
    // Build a boolean wall[][] array for easier processing
    std::vector<std::vector<bool>> wall(m.rows + 2, std::vector<bool>(m.cols + 2, false));
    for (int i = 0; i < m.rows + 2; i++)
    {
        for (int j = 0; j < m.cols + 2; j++)
        {
            if (m.maze[i][j] == m.wall)
            {
                wall[i][j] = true;
            }
        }
    }

    for (int i = 0; i < m.rows + 2; i++)
    {
        for (int j = 0; j < m.cols + 2; j++)
        {
            // Print the mouse if at the current cell
            if (i == m.currentCell.getRow() && j == m.currentCell.getCol())
            {
                os << "鼠";
                continue;
            }
            // Print the exit if at the current cell
            else if (i == m.exitCell.getRow() && j == m.exitCell.getCol())
            {
                os << " ♪";
                continue;
            }

            // Print wall characters based on neighboring walls
            if (wall[i][j])
            {
                bool up = (i > 0) && wall[i - 1][j];
                bool down = (i < m.rows + 1) && wall[i + 1][j];
                bool left = (j > 0) && wall[i][j - 1];
                bool right = (j < m.cols + 1) && wall[i][j + 1];

                if (up && down && right && left)
                {
                    os << "─┼";
                }
                else if (up && down && right)
                {
                    os << " ├";
                }
                else if (up && down && left)
                {
                    os << "─┤";
                }
                else if (down && left && right)
                {
                    os << "─┬";
                }
                else if (up && left && right)
                {
                    os << "─┴";
                }
                else if (up && right)
                {
                    os << " └";
                }
                else if (up && left)
                {
                    os << "─┘";
                }
                else if (down && right)
                {
                    os << " ┌";
                }
                else if (down && left)
                {
                    os << "─┐";
                }
                else if (up || down)
                {
                    os << " │";
                }
                else if (right || left)
                {
                    os << "──";
                }
                else
                {
                    // Isolated wall
                    os << " ※";
                }
            }
            else
            {
                // Open cell => two spaces
                os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}

// ---------------------------------------------------------------------
// getNeighbors: Returns all valid neighboring cells (Right, Left, Down, Up)
//           that are open (passage) or the exit (exitMarker).
// ---------------------------------------------------------------------
std::vector<Cell> Maze::getNeighbors(const Cell &pos) const
{
    std::vector<Cell> neighbors;
    int r = pos.row;
    int c = pos.col;

    // Right
    if (maze[r][c + 1] == passage || maze[r][c + 1] == exitMarker)
    {
        neighbors.emplace_back(r, c + 1);
    }
    // Left
    if (maze[r][c - 1] == passage || maze[r][c - 1] == exitMarker)
    {
        neighbors.emplace_back(r, c - 1);
    }
    // Down
    if (maze[r + 1][c] == passage || maze[r + 1][c] == exitMarker)
    {
        neighbors.emplace_back(r + 1, c);
    }
    // Up
    if (maze[r - 1][c] == passage || maze[r - 1][c] == exitMarker)
    {
        neighbors.emplace_back(r - 1, c);
    }

    return neighbors;
}

// ---------------------------------------------------------------------
// markVisited: Marks a cell as visited by setting it to 'visited'
// unless it's 'exitMarker' or 'entryMarker'.
// ---------------------------------------------------------------------
void Maze::markVisited(const Cell &cell)
{
    if (maze[cell.row][cell.col] != exitMarker && maze[cell.row][cell.col] != entryMarker)
    {
        maze[cell.row][cell.col] = visited;
    }
}

// ---------------------------------------------------------------------
// Getters for entry and exit positions
// ---------------------------------------------------------------------
Cell Maze::getEntry() const
{
    return entryCell;
}

Cell Maze::getExit() const
{
    return exitCell;
}

// ---------------------------------------------------------------------
// solveMaze: Implements the maze-solving algorithm using internal stacks.
// Returns true if the exit is found, false otherwise.
// ---------------------------------------------------------------------
bool Maze::exitMaze()
{
    // Push the entry position onto the path stack
    wayBack.push(entryCell);
    currentCell = entryCell; // Initialize current position

    bool foundExit = false;

    // Maze-solving loop
    while (!wayBack.empty() && !foundExit)
    {
        // Current position of the mouse is at the top of wayBack
        Cell current = wayBack.top();
        currentCell = current; // Update current position for visualization

        // Animate: clear the screen and print the current state of the maze
        clearScreen();
        std::cout << *this;                                         // Use overloaded << operator
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for animation

        // Check if the exit has been reached
        if (current == exitCell)
        {
            foundExit = true;
            break;
        }

        // Get all valid neighbors from the current position
        std::vector<Cell> neighbors = getNeighbors(current);

        if (neighbors.empty())
        {
            // No untried neighbors; backtrack by popping the current cell
            wayBack.pop();
        }
        else
        {
            // Push all neighbors onto mazeStack in reverse order so that
            // the first neighbor is processed first (Right, Left, Down, Up)
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it)
            {
                mazeStack.push(*it);
            }

            // Take the next neighbor to explore
            Cell nextPos = mazeStack.top();
            mazeStack.pop();

            // Mark the cell as visited
            markVisited(nextPos);

            // Push the new position onto the path stack
            wayBack.push(nextPos);
        }
    }

    // Final display of the maze after solving
    clearScreen();
    std::cout << *this; // Use overloaded << operator

    // Display the result of the maze-solving attempt
    if (foundExit)
    {
        std::cout << "\nThe mouse found the exit!\n";
    }
    else
    {
        std::cout << "\nNo path found. The mouse is trapped.\n";
    }

    return foundExit;
}
