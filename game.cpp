#include "game.h"
#include <iostream>

Game::Game(){
	board = new Board();
}

void Game::play(){
    Player* p = new Player(true);
	board->init();
	board->displayBoard();
	board->legalMoves(p,this->moves);
	printMoves();
	return;
}

void Game::printMoves(){
    int s_col;
    int s_row;
    int e_col;
    int e_row;
    int i = 0;
	for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++,i++){
		s_col = it->start[0];
		s_row = 2 * it->start[1];
		e_col = it->end[0];
		e_row = 2 * it->end[1];
        if (s_col % 2) s_row++;
        if (e_col % 2) e_row++;
        std::cout << "Move " << i << ": " <<
        '(' << s_col << ',' <<  s_row << ')' <<
        ',' << '(' << e_col << ',' <<  e_row << ')' << std::endl;

	}
}

int main() {

	Game g;

	g.play();

    return 0;
}
