#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
    int start[2];
    int end[2];
    Move();
    Move(int startcol, int startrow, int endcol, int endrow);
};

#endif