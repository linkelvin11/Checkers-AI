#ifndef BOARD_H
#define BOARD_H


#include "move.h"
#include "player.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>


class Board
{


public:
    int board[8][4] = {};
    Board();
    ~Board();
    
    void checkMoves(Player *p, std::vector<Move> &moves);
    bool checkJumps(Player *p, std::vector<Move> &moves);
    bool jumpsFrom(Player *p, int col, int row, std::vector<Move> &moves);
    void terminalJumps(Player *p, std::vector<Move> &moves);
    bool legalMoves(Player *p, std::vector<Move> &moves);
    void kingMe(int row, int col);
    void makeMove(int start[], int middle[], int end[], bool isJump);
    void makeMove(Move *move);
    void makeSingleMove(Move *move);

    int alphaBeta(Player *maxPlayer, Player *currentPlayer, Player *opponent, int alpha, int beta, int depth, Move* currentMove, bool maximize);
    
    void init();
    
    const char* uniPiece(int piece);
    void copyBoard(Board *src);
    void readBoard();
    void displayBoard();

    int score(Player *p);
};

#endif