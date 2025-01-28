#include "../include/GUI.h"

GUI::GUI(Maze &maze, float cell_x, float cell_y)
    : mazeData(maze), cell_x(cell_x), cell_y(cell_y),
      window(sf::VideoMode(800, 800), "Where's the Rat?")
{
    rat.setSize(sf::Vector2f(cell_x, cell_y));
    rat.setFillColor(sf::Color::Red);
    initializeGrid();
}

void GUI::initializeGrid()
{
    int rows = mazeData.getRows() + 2;
    int cols = mazeData.getCols() + 2;
    grid.resize(rows, std::vector<sf::RectangleShape>(cols));

    cell_x = 800 / cols;
    cell_y = 800 / rows;
    rat.setSize(sf::Vector2f(cell_x, cell_y));
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            grid[row][col].setSize(sf::Vector2f(cell_x, cell_y));
            grid[row][col].setPosition(col * cell_x, row * cell_y);
            grid[row][col].setOutlineColor(sf::Color::Black);
            grid[row][col].setOutlineThickness(1.0f);
            switch (mazeData.getCellType(row, col))
            {
            case '0':
                grid[row][col].setFillColor(sf::Color::White);
                break;
            case '1':
                grid[row][col].setFillColor(sf::Color::Blue);
                break;
            case 'e':
                grid[row][col].setFillColor(sf::Color::Green);
                break;
            case '.':
                grid[row][col].setFillColor(sf::Color::White);
                break;
            case 'm':
                grid[row][col].setFillColor(sf::Color::Red);
                break;
            default:
                grid[row][col].setFillColor(sf::Color::Transparent);
                break;
            }
        }
    }
}

void GUI::updateGrid()
{
    for (int row = 0; row < mazeData.getRows(); ++row)
    {
        for (int col = 0; col < mazeData.getCols(); ++col)
        {
            switch (mazeData.getCellType(row, col))
            {
            case '0':
                grid[row][col].setFillColor(sf::Color::White);
                break;
            case '1':
                grid[row][col].setFillColor(sf::Color::Blue);
                break;
            case 'e':
                grid[row][col].setFillColor(sf::Color::Green);
                break;
            case '.':
                grid[row][col].setFillColor(sf::Color::White);
                break;
            case 'm':
                grid[row][col].setFillColor(sf::Color::White);
                break;
            default:
                grid[row][col].setFillColor(sf::Color::Blue);
                break;
            }
        }
    }
}

void GUI::drawGrid()
{
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            window.draw(cell);
        }
    }
}

void GUI::updateRatPosition(int row, int col)
{
    rat.setPosition(col * cell_x, row * cell_y);
}

void GUI::drawRat()
{
    window.draw(rat);
}

void GUI::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        bool found = mazeData.exitMaze(*this);
        if (found)
        {
            window.close();
        }
    }
}