#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include <vector>
#include <random>
#include "Maze.hpp"
#include "MazeGenerator.hpp"


class generator : public MazeGenerator
{
public:
    virtual void Algorithm(Maze& maze, int X, int Y,std::vector<std::vector<int>> checker, std::vector<std::pair<int,int>> visited, std::default_random_engine engine, std::vector<Direction> direction);

    virtual void generateMaze(Maze& maze);

};

#endif
