
#include "board.h"  

Player::Player(bool first)
{
    if (first)
    {
        men = 1;
        king = 2;
        return;
    }
    men = 3;
    king = 4;
    return;
}

Board::Board()
{
    return;
}

bool Board::checkMoves(int** board, Player *p)
{
    return true;
}
bool Board::checkJumps(int** board, Player *p)
{
    return true;
}

bool Board::legalMoves(int** board, Player *p)
{
    Board::checkJumps(board,p);
    Board::checkMoves(board,p);
    return 0;
}

int Board::makeMove(int start, int end, int** board)
{
    return 0;
}

int main()
{
    return 0;
}