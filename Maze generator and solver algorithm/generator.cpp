#include "generator.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, generator, "Mina's Algorithm (Required)");

void generator::Algorithm(Maze& maze, int X, int Y, std::vector<std::vector<int>> checker, std::vector<std::pair<int,int>> visited, std::default_random_engine engine, std::vector<Direction> direction)
{
    if(visited.empty())
        return;
    else
    {
        direction.clear();

        if(maze.wallExists(X,Y,Direction::up) && Y-1 >=0)
            if(checker[Y-1][X]==0)
                direction.push_back(Direction::up);
        if(maze.wallExists(X,Y,Direction::down) && Y+1 < maze.getHeight())
            if(checker[Y+1][X]==0)
                direction.push_back(Direction::down);
        if(maze.wallExists(X,Y,Direction::right) && X+1 < maze.getWidth())
            if(checker[Y][X+1]==0)
                direction.push_back(Direction::right);
        if(maze.wallExists(X,Y,Direction::left) && X-1 >= 0)
            if (checker[Y][X-1]==0)
                direction.push_back(Direction::left);

       if(!direction.empty())
        {
            int size = direction.size()-1;
            std::uniform_int_distribution<int> distribution{0,size};
            int random_num = distribution(engine);    
            switch(direction[random_num])
            {
                case Direction::up:
                    maze.removeWall(X,Y,Direction::up);
                    --Y;
                    break;
                case Direction::down:
                    maze.removeWall(X,Y,Direction::down);
                    ++Y;
                    break;
                case Direction::right:
                    maze.removeWall(X,Y,Direction::right);
                    ++X;
                    break;
                case Direction::left:
                    maze.removeWall(X,Y,Direction::left);
                    --X;
                    break;
            }
            
            checker[Y][X] = 1;
            visited.push_back(std::make_pair(X,Y));
        }
        else
        {
            visited.pop_back();
            if(!visited.empty())
            {
                X = visited[visited.size()-1].first;
                Y = visited[visited.size()-1].second;
            }
        }
     
    
    Algorithm(maze,X,Y, checker, visited, engine,direction);
    } 
    
}

void generator :: generateMaze(Maze& maze)
{
    maze.addAllWalls();

    int my_cols = maze.getWidth();
    int my_rows = maze.getHeight();

    std::random_device my_device;
    std::default_random_engine my_engine(my_device());

    std::uniform_int_distribution<int> startX{0,my_cols-1};
    std::uniform_int_distribution<int> startY{0,my_rows-1};

    int x = startX(my_engine);
    int y = startY(my_engine);

    std::vector<Direction> my_direction;
    std::vector<std::pair<int,int>> my_visited;

    std::vector<std::vector<int>> my_checker(my_rows, std::vector<int>(my_cols, 0));

    my_visited.push_back(std::make_pair(x,y));
    my_checker[y][x] = 1;

    generator::Algorithm(maze, x, y, my_checker,  my_visited, my_engine, my_direction);
    
}
