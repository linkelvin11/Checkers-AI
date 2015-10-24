#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    int men;
    int king;
    bool isComputer;

    Player(bool first, bool AI);
};

#endif