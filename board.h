#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include "player.h"
#include <iostream>
#include <vector>


class Board
{


public:
    int moveCtr;
    Move* moves;
    int board[8][4] = {};
    Board();
    ~Board();
    void checkMoves(Player *p, std::vector<Move> &moves);
    bool checkJumps(Player *p, std::vector<Move> &moves);
    void legalMoves(Player *p, std::vector<Move> &moves);
    int makeMove(int start, int end, int** b);
    void printMoves();
    void init();
    const char* uniPiece(int piece);
    void displayBoard();
};

#endif