#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    int men;
    int king;
    bool isComputer = false;
    bool isIntelligent = false;

    Player(bool first);
};

#endif