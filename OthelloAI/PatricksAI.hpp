#ifndef PATRICKSAI_HPP
#define PATRICKSAI_HPP

#include "OthelloAI.hpp"
using namespace std;

namespace pmang
{
	class PatricksAI: public OthelloAI
	{
	public:
		virtual pair<int,int> chooseMove(const OthelloGameState& state);
		vector<pair<int,int>> findMoves(const OthelloGameState& s, const OthelloBoard& board);
		int search(OthelloGameState& s, int depth, OthelloCell& myColor);
		int eval(OthelloGameState& state,OthelloCell& turn);
		pair<int,int> getHighestEval(int bestEval,int currentEval, pair<int,int> bestMove, pair<int,int> currentMove);
	private:
		//int min=100;
		//int max=0;
		//int evaluation;
		//pair<int,int> bestMove;
	};
}

#endif