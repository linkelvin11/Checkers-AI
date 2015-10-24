#include "game.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

unsigned int sleeptime = 500000;

Game::Game(){
    board = new Board();
}

void Game::play(){
    int moveCtr = 0;
    int moveNumber;
    int col;
    int row;
    Player* first = new Player(true,true);
    Player* second = new Player(false,true);
    Player* currentPlayer = first;
    board->init();
    board->readBoard();
    while(true){
        ++moveCtr%2?currentPlayer = first:currentPlayer = second;
        board->displayBoard();
        board->legalMoves(currentPlayer,moves);
        if (!currentPlayer->isComputer)printMoves();
        else usleep(sleeptime);
        if (moves.size() == 0)
        {
            std::cout << "game over\n";
            return;
        }
        if (currentPlayer->isComputer)
            moveNumber = rand() % moves.size();
        else for (moveNumber = 1000; moveNumber >= moves.size();) {
            std::cout << "type in which move you'd like\n";
            std::cin >> moveNumber;
        }
        //board->makeMove(moves[moveNumber].start,moves[moveNumber].end,moves[moveNumber].isJump);
        board->makeMove(&moves[moveNumber]);
        if (moves[moveNumber].isJump) {
            col = moves[moveNumber].end[0];
            row = moves[moveNumber].end[1];
            moves.clear();
            while (board->jumpsFrom(currentPlayer,col,row,moves)) {
                board->displayBoard();
                if (!currentPlayer->isComputer)printMoves();
                else usleep(sleeptime);
                do {
                    if (currentPlayer->isComputer)
                        moveNumber = rand() % moves.size();
                    else {
                        std::cout << "You just jumped! Jump again!\n";
                        std::cin >> moveNumber;
                    }
                }
                while (moveNumber >= moves.size());
                //board->makeMove(moves[moveNumber].start,moves[moveNumber].end,moves[moveNumber].isJump);
                board->makeMove(&moves[moveNumber]);
                col = moves[moveNumber].end[0];
                row = moves[moveNumber].end[1];
                moves.clear();
            }
        }
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
