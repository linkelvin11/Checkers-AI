
#include "board.h"
#include <iostream>

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
                    // check bottom right
                    if(row && !this->board[col+1][row-1] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row-1);
                    }
                    // check top left
                    if(col && !this->board[col-1][row] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    //check bottom left
                    if(col && row && !this->board[col-1][row-1] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row-1);
                    }
                }
                else { // odd columns (right side)
                    // check bottom right
                    if ((col+1)%4 && !this->board[col+1][row] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row);
                    }
                    // check top right
                    if ((col+1)%4 && !this->board[col+1][row+1] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col+1,row+1);
                    }
                    // check bottom left
                    if (!this->board[col-1][row] && (down || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    //check top left
                    if ((row+1)%4 && !this->board[col-1][row+1] && (up || this->board[col][row] == king)) {
                        this->moves[moveCtr++] = Move(col,row,col-1,row+1);
                    }
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
    int s_col;
    int s_row;
    int e_col;
    int e_row;
    for (int i = 0; i < this->moveCtr; i++){
        s_col = this->moves[i].start[0];
        s_row = 2 * this->moves[i].start[1];
        e_col = this->moves[i].end[0];
        e_row = 2 * this->moves[i].end[1];
        if (s_col % 2) s_row++;
        if (e_col % 2) e_row++;
        std::cout << "Move " << i << ": " <<
        '(' << s_col << ',' <<  s_row << ')' <<
        ',' << '(' << e_col << ',' <<  e_row << ')' << std::endl;
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
    Player* p = new Player(false);
    Board* b = new Board();
    b->init();
    b->displayBoard();
    b->checkMoves(p);
    b->printMoves();
    return 0;
}
