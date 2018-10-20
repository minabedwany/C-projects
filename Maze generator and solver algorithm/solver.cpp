#include "solver.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, solver, "Mina's Solver(Required)");


void algorithm(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<int>> &my_checker)
{

    if(mazeSolution.isComplete())
        return;
    else
    {
        if(!maze.wallExists(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, Direction::down) && my_checker[mazeSolution.getCurrentCell().second+1][mazeSolution.getCurrentCell().first]==0)
        {
            mazeSolution.extend(Direction::down);
            my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first] = 1;
            algorithm(maze, mazeSolution, my_checker);
            return;
        }

        if(!maze.wallExists(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, Direction::up) && my_checker[mazeSolution.getCurrentCell().second-1][mazeSolution.getCurrentCell().first]==0)
        {
            mazeSolution.extend(Direction::up);
            my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first] = 1;
            algorithm(maze, mazeSolution, my_checker);
            return;
        }


        if(!maze.wallExists(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, Direction::right) && my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first+1]==0)
        {
            mazeSolution.extend(Direction::right);
            my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first] = 1;
            algorithm(maze, mazeSolution, my_checker);
            return;
        }



        if(!maze.wallExists(mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second, Direction::left) && my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first-1]==0)
        {
            mazeSolution.extend(Direction::left);
            my_checker[mazeSolution.getCurrentCell().second][mazeSolution.getCurrentCell().first] = 1;
            algorithm(maze, mazeSolution, my_checker);
            return;
        }
        
       
        else
        {
            mazeSolution.backUp();
            algorithm(maze, mazeSolution, my_checker);
            return;
        }
    }    

}
 

void solver :: solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();

    int cols = mazeSolution.getWidth();
    int rows = mazeSolution.getHeight();

    std::vector<std::vector<int>> checker(rows, std::vector<int>(cols, 0));

    checker[0][0] = 1;

    algorithm(maze, mazeSolution, checker);

}

