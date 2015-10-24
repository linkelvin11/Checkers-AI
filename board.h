#ifndef BOARD_H
#define BOARD_H


#include "move.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class Board
{


public:
    int board[8][4] = {};
    Board();
    ~Board();
    void checkMoves(Player *p, std::vector<Move> &moves);
    bool checkJumps(Player *p, std::vector<Move> &moves);
    void jumpsFrom(Player *p, int col, int row, std::vector<Move> &moves);
    void legalMoves(Player *p, std::vector<Move> &moves);
    void makeMove(int start[], int end[], bool isJump);
    void init();
    const char* uniPiece(int piece);
    void readBoard();
    void displayBoard();
};

#endif