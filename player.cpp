#include "player.h"

Player::Player(bool first) {
    if (first) {
        men = 1;
        king = 2;
    }
    else {
        men = 3;
        king = 4;
    }
    isComputer = false;
    isIntelligent = false;
    return;
}
