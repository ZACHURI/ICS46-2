#ifndef PATRICKSMAZESOLVER_HPP
#define PATRICKSMAZESOLVER_HPP


#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <utility>
using namespace std;

class PatricksMazeSolver: public MazeSolver
{
public:
	PatricksMazeSolver();
	void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
	void recursiveSolver(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
	vector<Direction> checkForPaths(int x, int y,const Maze& maze, MazeSolution& mazeSolution);
	Direction opposite(Direction d);
	pair<int,int> getCell(int x, int y, Direction d);
private:
 	vector<pair<int,int>> visited;                                                                           
};

#endif
