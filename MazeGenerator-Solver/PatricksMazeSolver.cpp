#include "PatricksMazeSolver.hpp"
#include "Direction.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp> 
using namespace std;
#include <algorithm>
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver,PatricksMazeSolver,"PatricksMazeSolver(Required)");

PatricksMazeSolver::PatricksMazeSolver()
{

}

//solve the maze
void PatricksMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();
  	pair<int,int> starting = mazeSolution.getStartingCell();
  	recursiveSolver(starting.first,starting.second,maze,mazeSolution);                     
}

//helper function to return opposite direction
Direction PatricksMazeSolver::opposite(Direction d)
{
	if(d==Direction::right)
		return Direction::left;
	else if(d==Direction::left)
		return Direction::right;
	else if(d==Direction::up)
		return Direction::down;
	else if(d==Direction::down)
		return Direction::up; 
}

//check for open paths at a particular point (x,y)
vector<Direction> PatricksMazeSolver::checkForPaths(int x, int y,const Maze& maze, MazeSolution& mazeSolution)
{
	vector<Direction> track = {};
	vector<Direction> d = {Direction::right,Direction::left
		,Direction::up,Direction::down};
	pair<int,int> cell;
	for(int i = 0;i<4;i++)
	{
		cell = getCell(x,y,d[i]);
		if(!maze.wallExists(x,y,d[i]) && find(visited.begin(),visited.end(),cell)==visited.end())
		{
			track.push_back(d[i]);
		}
	}
	return track;
}

//helper function to get the cell in a particular direction from (x,y)
pair<int,int> PatricksMazeSolver::getCell(int x, int y, Direction d)
{
	pair<int,int> temp;
	if(d == Direction::right)
	{ 
		temp = make_pair(x+1,y);
	}
	else if(d == Direction::up)
	{
		temp = make_pair(x,y-1);
	}
	else if(d == Direction::down)
	{
		temp = make_pair(x,y+1);
	}
	else if(d == Direction::left)
	{
		temp = make_pair(x-1,y);
	}
	return temp;
}

//recursive maze solver that uses a depth first approach
void PatricksMazeSolver::recursiveSolver(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
{
	Direction m;
	pair<int,int> cell;
	int i;
	vector<Direction> paths = checkForPaths(x,y,maze,mazeSolution);
	if(mazeSolution.isComplete())
		return;
	if(paths.size()>0)
	{
		for(i=0;i<paths.size();i++)
		{
			m = paths[i];
			if(find(visited.begin(),visited.end(),getCell(x,y,m))==visited.end())
			{
				if(!mazeSolution.isComplete())
					mazeSolution.extend(m);
				cell = mazeSolution.getCurrentCell();
				visited.push_back(cell);
				recursiveSolver(cell.first,cell.second,maze,mazeSolution);
			}
		}
	}
	else if(paths.size()==0)
	{

		mazeSolution.backUp();
		cell = mazeSolution.getCurrentCell();
		if(cell == mazeSolution.getStartingCell())
			return;
		recursiveSolver(cell.first,cell.second,maze,mazeSolution);
	}
	
}

