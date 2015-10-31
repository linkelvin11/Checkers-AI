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
#include <chrono>


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
    void recurseJumps(Player*p, std::vector<Move> &currentMoves, std::vector<Move> &moves);
    bool legalMoves(Player *p, std::vector<Move> &moves);
    bool kingMe(int row, int col);
    bool makeMove(int start[], int middle[], int end[], bool isJump);
    bool makeMove(Move *move);
    bool makeSingleMove(Move *move);

    int alphaBeta(Player *maxPlayer, Player *currentPlayer, Player *opponent, int alpha, int beta, int depth, Move* currentMove, bool maximize);
    
    void init();
    
    const char* uniPiece(int piece);
    void copyBoard(Board *src);
    void readBoard();
    void displayBoard();

    int score(Player *p);
    int popCount(Player *p);
};

#endif