#include "move.h"
#include "board.h"

Move::Move() {
    start[0] = 0;
    start[1] = 0;
    end[0] = 0;
    end[1] = 0;
}

Move::Move(int startcol, int startrow, int endcol, int endrow, Board* b) {
    start[0] = startcol;
    start[1] = startrow;
    end[0] = endcol;
    end[1] = endrow;
    isJump = false;
    board = new Board();
    board->copyBoard(b);
    board->makeSingleMove(this);
    //board->makeSingleMove(start,end,Jump);
}

Move::Move(int startcol, int startrow, int midcol, int midrow, int endcol, int endrow, bool Jump, Board* b) {
    start[0] = startcol;
    start[1] = startrow;
    middle[0] = midcol;
    middle[1] = midrow;
    end[0] = endcol;
    end[1] = endrow;
    isJump = Jump;
    board = new Board();
    board->copyBoard(b);
    board->makeSingleMove(this);
    //board->makeSingleMove(start,end,Jump);
}