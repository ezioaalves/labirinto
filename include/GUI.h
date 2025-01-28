#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "../include/Maze.h"

class GUI
{
private:
    sf::RenderWindow window;
    sf::RectangleShape rat;
    std::vector<std::vector<sf::RectangleShape>> grid;
    Maze &mazeData;
    float cell_x;
    float cell_y;

    void initializeGrid();
    void updateGrid();
    void drawGrid();
    void drawRat();

public:
    GUI(Maze &maze, float cell_x = 40.0f, float cell_y = 40.0f);
    void run();
    void updateRatPosition(int row, int col);

    friend class Maze;
};
#endif