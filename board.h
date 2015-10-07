#ifndef BOARD_H
#define BOARD_H

class Player
{
public:
    int men;
    int king;
    Player(bool first);
};

class Board
{
    int b[8][4] = {};

public:
    Board();
    bool checkMoves(int** board, Player *p);
    bool checkJumps(int** board, Player *p);
    bool legalMoves(int** board, Player *p);
    int makeMove(int start, int end, int** b);
};

#endif