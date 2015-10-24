#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <vector>

class Game {

Board* board = new Board();
std::vector<Move> moves;


public:
Game();
void play();

void printMoves();

};


#endif