#ifndef BOARD_H
#define BOARD_H

class Move
{
public:
    int start[2];
    int end[2];
    Move();
    Move(int startcol, int startrow, int endcol, int endrow);
};

class Player
{
public:
    int men;
    int king;
    Player(bool first);
};

class Board
{

    int moveCtr;
    Move* moves;
public:
    int board[8][4] = {};
    Board();
    ~Board();
    bool checkMoves(Player *p);
    bool checkJumps(int** board, Player *p);
    bool legalMoves(int** board, Player *p);
    int makeMove(int start, int end, int** b);
    void printMoves();
    void init();
    const char* uniPiece(int piece);
    void displayBoard();
};

#endif