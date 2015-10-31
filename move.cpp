#include "move.h"
#include "board.h"

Move::Move() {
    start[0] = 0;
    start[1] = 0;
    middle[0] = 0;
    middle[1] = 0;
    end[0] = 0;
    end[1] = 0;
}
Move::~Move() {
    delete board;
}

Move::Move(const Move& src){
    start[0] = src.start[0];
    start[1] = src.start[1];
    middle[0] = src.middle[0];
    middle[1] = src.middle[1];
    end[0] = src.end[0];
    end[1] = src.end[1];
    isJump = src.isJump;
    board = new Board();
    board->copyBoard(src.board);
}

Move& Move::operator=(const Move& src){
    start[0] = src.start[0];
    start[1] = src.start[1];
    middle[0] = src.middle[0];
    middle[1] = src.middle[1];
    end[0] = src.end[0];
    end[1] = src.end[1];
    isJump = src.isJump;
    board = new Board();
    board->copyBoard(src.board);
}

Move::Move(int startcol, int startrow, int endcol, int endrow, Board* b) {
    start[0] = startcol;
    start[1] = startrow;
    middle[0] = 0;
    middle[1] = 0;
    end[0] = endcol;
    end[1] = endrow;
    isJump = false;
    board = new Board();
    board->copyBoard(b);
    board->makeSingleMove(this);
}

Move::Move(int startcol, int startrow, int midcol, int midrow, int endcol, int endrow, bool Jump, Board* b) {
    start[0] = startcol;
    start[1] = startrow;
    middle[0] = midcol;
    middle[1] = midrow;
    end[0] = endcol;
    end[1] = endrow;
    board = new Board();
    board->copyBoard(b);
    isJump = Jump;
    if (board->makeSingleMove(this))
        isJump = false;
}

void Move::killTree(){
    for (std::vector<Move>::iterator it = nextMoves.begin(); it != nextMoves.end(); it++){

    }
}