#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

class Game {

Board* board = new Board();
std::vector<Move> moves;


public:
Game();
~Game();
void play();

void printMoves();
Move* alphaBeta_init(Player *maxplayer, Player *minplayer, int maxdepth);

};


#endif