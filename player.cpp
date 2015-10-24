#include "player.h"

Player::Player(bool first, bool AI) {
    if (first) {
        men = 1;
        king = 2;
    }
    else {
        men = 3;
        king = 4;
    }
    isComputer = AI;
    return;
}
