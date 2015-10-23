#ifndef MOVE_H
#define MOVE_H

class Board;

#include <vector>

class Move
{
public:
	std::vector<Move> nextMoves;
	Board* board;
	bool isJump;
    int start[2];
    int end[2];
    Move();
    Move(int startcol, int startrow, int endcol, int endrow, bool Jump, Board* b);
};

#endif