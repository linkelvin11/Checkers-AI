#include "game.h"
#include <iostream>

Game::Game(){
    board = new Board();
}

void Game::play(){
    int moveCtr;
    int moveNumber;
    Player* first = new Player(true);
    Player* second = new Player(false);
    board->init();
    board->readBoard();

    while(true){
        board->displayBoard();
        board->legalMoves(second,this->moves);
        printMoves();
        std::cout << "type in which move you'd like\n";
        std::cin >> moveNumber;
        if (moveNumber > 1000)
            return;
        moves.clear();
    }
    return;
}

void Game::printMoves(){
    int s_col;
    int s_row;
    int e_col;
    int e_row;
    int i = 0;
    std::cout << "Total moves available: " << moves.size() << std::endl;
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
