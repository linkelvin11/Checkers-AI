#include "move.h"
#include "board.h"

Move::Move() {
    start[0] = 0;
    start[1] = 0;
    end[0] = 0;
    end[1] = 0;
}

Move::Move(int startcol, int startrow, int endcol, int endrow, bool Jump, Board* b) {
    start[0] = startcol;
    start[1] = startrow;
    end[0] = endcol;
    end[1] = endrow;
    isJump = Jump;
    board = b;
    //board->makeMove(start,end,Jump);

}