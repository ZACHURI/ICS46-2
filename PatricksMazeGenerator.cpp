#include <ics46/factory/DynamicFactory.hpp>
#include "PatricksMazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <stdlib.h>
using namespace std;
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,PatricksMazeGenerator,"PatricksMazeGenerator(Required)");

PatricksMazeGenerator::PatricksMazeGenerator()
{

}

void PatricksMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	visited.push_back(make_tuple(0,0));
	generatorRecursive(0,0,maze);
}

tuple<int,int> PatricksMazeGenerator::getCell(int x, int y, Direction d,Maze& maze)
{
	pair<int,int> temp;
	if(d == Direction::right && x != maze.getWidth()-1)
	{ 
		temp = make_tuple(x+1,y);
	}
	else if(d == Direction::up && y != 0)
	{
		temp = make_tuple(x,y-1);
	}
	else if(d == Direction::down && y != maze.getHeight()-1)
	{
		temp = make_tuple(x,y+1);
	}
	else if(d == Direction::left && x != 0)
	{
		temp = make_tuple(x-1,y);
	}
	return temp;
}

void PatricksMazeGenerator::checkForPaths(int x,int y,Maze& maze)
{
	bool added = false;
	vector<bool> index = {false,false,false,false};
	Direction d;
	while(added != true)
	{
		int direction = distribution(engine);
		switch(direction)
		{
			case 1: d = Direction::right; index[0]=true; break;
			case 2: d = Direction::up; index[1] = true; break;
			case 3: d = Direction::down; index[2] = true; break;
			case 4: d = Direction::left; index[3] = true; break;
		}
		//cout<<direction<<endl;
		temp = getCell(x,y,d,maze);
		if(find(visited.begin(),visited.end(),temp)==visited.end())
		{
			visited.push_back(temp);
			maze.removeWall(x,y,d);
			counter=2;
			added = true;
		}
		else if(index[0] == true && index[1] == true && index[2] == true && index[3] == true)
		{
			temp = visited[visited.size()-counter];
			//cout<<get<0>(temp)<<" "<<get<1>(temp)<<endl;
			if(counter < visited.size()-1)
				counter++;	
			added = true;
		}
	}
	return;
}

void PatricksMazeGenerator::generatorRecursive(int x, int y, Maze& maze)
{
	checkForPaths(x,y,maze);
	if(visited.size() == (maze.getWidth() * maze.getHeight()))
		return;
	else
		generatorRecursive(get<0>(temp),get<1>(temp),maze);
}		




