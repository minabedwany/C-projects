#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include <vector>


class solver : public MazeSolver
{
public:
    virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);

};

#endif
