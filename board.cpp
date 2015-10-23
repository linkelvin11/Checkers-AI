
#include "board.h"  
#include <iostream>

Move::Move() {
    start[0] = 0;
    start[1] = 0;
    end[0] = 0;
    end[1] = 0;
}

Move::Move(int startcol, int startrow, int endcol, int endrow) {
    start[0] = startcol;
    start[1] = startrow;
    end[0] = endcol;
    end[1] = endrow;
}

Player::Player(bool first) {
    if (first) {
        men = 1;
        king = 2;
        return;
    }
    men = 3;
    king = 4;
    return;
}

Board::Board() {
    moves = new Move[32];
    return;
}

Board::~Board() {
    delete[] moves;
    return;
}

void Board::init() {
    int row = 0;
    int col = 0;
    int pmen = 1;
    int omen = 3;
    for(col = 0; col < 8; col++) {
        this->board[col][0] = pmen;
        this->board[col][3] = omen;
    }
    for (col = 1; col < 8; col+=2) {
        this->board[col-1][1] = pmen;
        this->board[col][2] = omen;
    }
}

bool Board::checkMoves(Player *p)
{
    this->moveCtr = 0;
    bool down = false;
    bool up = false;
    p->men == 1 ? up = true: down = true;
    int king = p->king;
    for(int row = 0; row < 4; row++) { // go through rows
        for(int col = 0; col < 8; col++) { // go through columns
            if (this->board[col][row]) {
                if (!(col % 2)) { // even columns (left side)
                    // check top right
                    if(!this->board[col+1][row] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row);
                        std::cout << col << row << col+1 << row << std::endl;
                    }
                    else {} //check jump
                    // check bottom right
                    if(row && !this->board[col+1][row-1] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row-1);
                    }
                    else {} //check jump
                    // check top left
                    if(col && !this->board[col-1][row] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    else {} //check jump
                    //check bottom left
                    if(col && row && !this->board[col-1][row-1] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row-1);
                    }
                    else {} //check jump
                }
                else { // odd columns (right side)
                    // check bottom right
                    if ((col+1)%4 && !this->board[col+1][row] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row);
                    }
                    else {} //check jumps
                    // check top right
                    if ((col+1)%4 && !this->board[col+1][row+1] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row+1);
                    }
                    // check bottom left
                    if (!this->board[col-1][row] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    else {} //check jumps
                    //check top left
                    if ((row+1)%4 && !this->board[col-1][row+1] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row+1);
                    }
                    else {} //check jumps
                }
            }
        }
    }
    return true;
}

bool Board::checkJumps(int** board, Player *p) {
    return true;
}

bool Board::legalMoves(int** board, Player *p) {
    if (Board::checkJumps(board,p)) {
        //list the legal jumps
        return true;
    }
    if (Board::checkMoves(p)) {
        // list the legal moves
        return true;
    }
    return false;
}

void Board::printMoves(){
    for (int i = 0; i < this->moveCtr; i++){
        std::cout << this->moves[i].start[0] << this->moves[i].start[1] <<
         ',' << this->moves[i].end[0] << this->moves[i].end[1] << std::endl;
    }
}

int Board::makeMove(int start, int end, int** board) {
    return 0;
}

const char* Board::uniPiece(int piece) {
    switch(piece) {
        case 0://empty
            return "\u25A3";
        case 1://black piece
            return "\u25CE";
        case 2://black king
            return "\u2654";
        case 3://red piece
            return "\u25C9";
        case 4://red king
            return "\u265A";
    }
}

void Board::displayBoard() {
    int row = 0;
    int col = 0;
    int colID = 0;
    int rowID = 7;
    std::cout << "  ";
    for(col = 0; col < 8; col++) {
        std::cout << colID++ << " ";
    }
    std::cout << std::endl;
    char blank[10] = " \u25FB";
    for(row = 3; row > -1; row--) {
        std::cout << rowID;
        for (col = 1; col < 8; col+=2) {
            std::cout << blank << " " << uniPiece(this->board[col][row]); 
        }
        std::cout << " " << rowID-- << std::endl << rowID;
        for (col = 0; col < 8; col+=2) {
            std::cout << " " << uniPiece(this->board[col][row]) << blank;
        }
        std::cout << " " << rowID-- << std::endl;
    }
    std::cout << "  ";
    for(col = 0, colID = 0; col < 8; col++) {
        std::cout << colID++ << " ";
    }
    std::cout << std::endl;
    return;
}

int main() {
    Player* p = new Player(true);
    Board* b = new Board();
    b->init();
    b->displayBoard();
    b->checkMoves(p);
    b->printMoves();
    return 0;
}
