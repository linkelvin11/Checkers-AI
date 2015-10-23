#include "move.h"

Move::Move() {
    start[0] = 0;
    start[1] = 0;
    end[0] = 0;
    end[1] = 0;
}

Move::Move(int startcol, int startrow, int endcol, int endrow) {
    start[0] = startcol;
    start[1] = startrow;
    end[0] = endcol;
    end[1] = endrow;
}