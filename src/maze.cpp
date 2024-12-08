#include <fstream>
#include "../include/maze.h"

Maze::Maze(int cont, std::string fileName)
{
    std::ifstream file("../" + fileName + ".txt");
    std::pair<int, int> size;
    std::string s;
    if (cont > 1)
    {
        getline(file, s);
        int pos = s.find_first_of(" ");
        size.first = stoi(s.substr(0, pos));
        size.second = stoi(s.substr(pos + 1));
        char map[size.first + 2][size.second + 2];
        for (int x = 0; x < size.first + 2; x++)
        {
            map[0][x] = '1';
        }
        for (int y = 1; y <= size.second; y++)
        {
            map[y][0] = '1';
            if (getline(file, s))
            {
                for (int x = 0; x < size.first; x++)
                {
                    map[y][x + 1] = s[x];
                }
            }
            map[y][size.first + 1] = '1';
        }
        for (int x = 0; x < size.first + 2; x++)
        {
            map[size.second + 1][x] = '1';
        }
    }
    else
    {
        std::cout << "Insira o número de linhas:" << std::endl;
        std::cin >> size.first;
        std::cout << "Insira o número de colunas:" << std::endl;
        std::cin >> size.second;
        char map[size.first + 2][size.second + 2];
        for (int x = 0; x < size.first + 2; x++)
        {
            map[0][x] = '1';
        }
        for (int y = 1; y <= size.second; y++)
        {
            map[y][0] = '1';
            if (getline(file, s))
            {
                for (int x = 0; x < size.first; x++)
                {
                    map[y][x + 1] = s[x];
                }
            }
            map[y][size.first + 1] = '1';
        }
        for (int x = 0; x < size.first + 2; x++)
        {
            map[size.second + 1][x] = '1';
        }
    }
}