#ifndef PATRICKSMAZEGENERATOR_HPP
#define PATRICKSMAZEGENERATOR_HPP


#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
using namespace std;


 class PatricksMazeGenerator: public MazeGenerator
 {
 public:
 	PatricksMazeGenerator();
 	tuple<int,int> getCell(int x, int y, Direction d, Maze& maze);
 	void checkForPaths(int x,int y,Maze& maze);
 	void generateMaze(Maze& maze) override;
 	void generatorRecursive(int x, int y, Maze& maze);
 	//~PatricksMazeGenerator();
 private:
 	vector<tuple<int,int>> visited;
 	random_device device;
 	default_random_engine engine{device()};
 	uniform_int_distribution<int> distribution{1,4};
 	int counter = 2;
 	tuple<int,int> temp;
 };

 #endif 