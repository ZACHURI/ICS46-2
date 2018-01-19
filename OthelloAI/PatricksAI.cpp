#include <ics46/factory/DynamicFactory.hpp>
#include "PatricksAI.hpp"
#include "OthelloCell.hpp"
#include "OthelloGameState.hpp"
#include <vector>
using namespace std;
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,pmang::PatricksAI,"Patrick Mang's AI (Required)");


vector<pair<int,int>> pmang::PatricksAI::findMoves(const OthelloGameState& s, const OthelloBoard& board)
{
	vector<pair<int,int>> moves;
	for(int i=0;i<board.height();i++)
	{
		for(int p=0;p<board.width();p++)
		{
			if(s.isValidMove(p,i))
			{
				pair<int,int> validMove = make_pair(p,i);
				moves.push_back(validMove);	
			}
		}
	}
	return moves;
}

int pmang::PatricksAI::eval(OthelloGameState& state,OthelloCell& turn)
{
	int result = 0;
	const OthelloBoard& board = state.board();
	if(turn==OthelloCell::black)
	{
		result=state.blackScore()-state.whiteScore();
		if(board.cellAt(0,0)==OthelloCell::black)
			result+=50;
		else if(board.cellAt(0,board.height()-1)==OthelloCell::black)
			result += 50;
		else if(board.cellAt(board.width()-1,0)==OthelloCell::black)
			result += 50;
		else if(board.cellAt(board.width()-1,board.height()-1)==OthelloCell::black)
			result += 50;

		if(board.cellAt(0,1)==OthelloCell::black)
			result-=50;
		else if(board.cellAt(1,0)==OthelloCell::black)
			result -= 50;
		else if(board.cellAt(0,board.height()-2)==OthelloCell::black)
			result -= 50;
		else if(board.cellAt(1,board.height()-1)==OthelloCell::black)
			result -=50;
		else if(board.cellAt(board.width()-2,0)==OthelloCell::black)
			result -= 50;
		else if(board.cellAt(board.width()-1,1)==OthelloCell::black)
			result -= 50;
		else if(board.cellAt(board.width()-1,board.height()-2)==OthelloCell::black)
			result -= 50;
		else if(board.cellAt(board.width()-2,board.height()-1)==OthelloCell::black)
			result -= 50;
	}
	else
	{
		result=state.whiteScore()-state.blackScore();
		if(board.cellAt(0,0)==OthelloCell::white)
			result+=50;
		else if(board.cellAt(0,board.height()-1)==OthelloCell::white)
			result += 50;
		else if(board.cellAt(board.width()-1,0)==OthelloCell::white)
			result += 50;
		else if(board.cellAt(board.width()-1,board.height()-1)==OthelloCell::white)
			result += 50;

		if(board.cellAt(0,1)==OthelloCell::white)
			result-=50;
		else if(board.cellAt(1,0)==OthelloCell::white)
			result -= 50;
		else if(board.cellAt(0,board.height()-2)==OthelloCell::white)
			result -= 50;
		else if(board.cellAt(1,board.height()-1)==OthelloCell::white)
			result -=50;
		else if(board.cellAt(board.width()-2,0)==OthelloCell::white)
			result -= 50;
		else if(board.cellAt(board.width()-1,1)==OthelloCell::white)
			result -= 50;
		else if(board.cellAt(board.width()-1,board.height()-2)==OthelloCell::white)
			result -= 50;
		else if(board.cellAt(board.width()-2,board.height()-1)==OthelloCell::white)
			result -= 50;
		
	}
	return result;
}

pair<int,int> pmang::PatricksAI::getHighestEval(int bestEval,int currentEval, pair<int,int> bestMove, pair<int,int> currentMove)
{
	if(currentEval>bestEval)
	{
		bestEval = currentEval;
		bestMove.first = currentMove.first;
		bestMove.second = currentMove.second;
	}
	return bestMove;
}

int pmang::PatricksAI::search(OthelloGameState& s, int depth, OthelloCell& myColor)
{
	//OthelloBoard board = s.board();
	// vector<int> you;
	// vector<int> opponent;
	//int evaluation;
	//int eval;
	OthelloCell current;
	if(s.isBlackTurn())
		current = OthelloCell::black;
	else if(s.isWhiteTurn())
		current = OthelloCell::white;

	if(s.isGameOver())
	{
		return eval(s,current);
	}

	vector<pair<int,int>> moves = findMoves(s,s.board());

	if(depth == 0 or moves.size()==0) 
	{
		//cout<<"return"<<endl;
		return eval(s,current);
	}
	else if(current == myColor)
	{
		int max;
		for(int i=0;i<moves.size();i++)
		{
			//cout<<"first loop "<<i<<endl;
			unique_ptr<OthelloGameState> state = s.clone();
			state->makeMove(moves[i].first,moves[i].second);
			//evaluation = s.blackScore()-s.whiteScore();
			int evaluation = search(*state,depth-1,myColor); 
			if(i==0)
				max=evaluation; 
			else if(evaluation>=max)
				max=evaluation;                                
		}
		//cout<<max<<endl;
		return max;
	}
	else 
	{
		int min;
		for(int p=0;p<moves.size();p++)
		{
			//cout<<"second loop "<<p<<endl;
			unique_ptr<OthelloGameState> state = s.clone();
			state->makeMove(moves[p].first,moves[p].second);
			//evaluation = s.whiteScore()-s.blackScore();
			//eval = max-min;
			int evaluation = search(*state,depth-1,myColor);
			if(p==0)
				min=evaluation;
			else if(evaluation<=min)
				min=evaluation;
		}
		// cout<<min<<endl;
		return min;
	}
}

pair<int,int> pmang::PatricksAI::chooseMove(const OthelloGameState& state)
{
	int moveEvaluation;
	int bestEval = -200;
	pair<int,int> bestMove = make_pair(0,0);
	vector<pair<int,int>> moves = findMoves(state,state.board());
	OthelloCell myColor;
	if(state.isBlackTurn())
		myColor = OthelloCell::black;
	else
		myColor = OthelloCell::white;
	//cout<<moves[1].first<<" "<<moves[1].second<<endl;
	unique_ptr<OthelloGameState> s = state.clone();
	//s->makeMove(moves[i].first,moves[i].second);
	moveEvaluation = search(*s,3,myColor);
	for(int i=0;i<moves.size();i++)
	{
		bestMove = getHighestEval(bestEval,moveEvaluation,bestMove,moves[i]);
	}
	//cout<<"break"<<endl;
	//cout<<moveEvaluation[2]<<endl;
	cout<<bestMove.first<<" "<<bestMove.second<<endl;
	return bestMove;
}
