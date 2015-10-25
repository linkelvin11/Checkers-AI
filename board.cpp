
#include "board.h"
#include <typeinfo>


Board::Board() {
    return;
}

Board::~Board() {
    return;
}

void Board::init() {
    int row = 0;
    int col = 0;
    int pmen = 1;
    int omen = 3;
    for(col = 0; col < 8; col++) {
        board[col][0] = pmen;
        board[col][3] = omen;
    }
    for (col = 1; col < 8; col+=2) {
        board[col-1][1] = pmen;
        board[col][2] = omen;
    }
}

void Board::checkMoves(Player *p, std::vector<Move> &moves)
{
    bool down = false;
    bool up = false;
    p->men == 1 ? up = true: down = true;
    int king = p->king;
    for(int row = 0; row < 4; row++) { // go through rows
        for(int col = 0; col < 8; col++) { // go through columns
            if (board[col][row] == p->men || board[col][row] == p->king) {
                if (!(col % 2)) { // even columns (left side)
                    // check top right
                    if(!board[col+1][row] && (up || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col+1,row,this));
                    }
                    // check bottom right
                    if(row && !board[col+1][row-1] && (down || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col+1,row-1,this));
                    }
                    // check top left
                    if(col && !board[col-1][row] && (up || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col-1,row,this));
                    }
                    //check bottom left
                    if(col && row && !board[col-1][row-1] && (down || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col-1,row-1,this));
                    }
                }
                else { // odd columns (right side)
                    // check bottom right
                    if ((col+1)%8 && !board[col+1][row] && (down || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col+1,row,this));
                    }
                    // check top right
                    if ((col+1)%8 && (row+1)%4 && !board[col+1][row+1] && (up || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col+1,row+1,this));
                    }
                    // check bottom left
                    if (!board[col-1][row] && (down || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col-1,row,this));
                    }
                    //check top left
                    if ((row+1)%4 && !board[col-1][row+1] && (up || board[col][row] == king)) {
                        moves.push_back(Move(col,row,col-1,row+1,this));
                    }
                }
            }
        }
    }
    return;
}

bool Board::checkJumps(Player *p, std::vector<Move> &moves) {
    for(int row = 0; row < 4; row++) { // go through rows
        for(int col = 0; col < 8; col++) { // go through columns
            this->jumpsFrom(p,col,row,moves);
        }
    }
    if (moves.size() == 0) // check if any jumps were detected
        return false;
    // for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
    //     it->board->checkJumps(p,it->nextMoves);
    // }
    return true;
}

bool Board::jumpsFrom(Player*p, int col, int row, std::vector<Move> &moves) {
    bool down = false;
    bool up = false;
    p->men == 1 ? up = true: down = true;
    int king = p->king;
    int omen = (p->men == 1 ? 3 : 1);
    int oking = (p->men == 1 ? 4 : 2);
    if (board[col][row] == p->men || board[col][row] == p->king) {
        if (!(col % 2)) { // even columns (left side)
            // check top right
            if( (row+1)%4 && (col+2)%8 &&
                (board[col+1][row] == omen || board[col+1][row] == oking) &&
                !board[col+2][row+1] &&
                (up || board[col][row] == king))
            {
                moves.push_back(Move(col,row,col+1,row,col+2,row+1,true,this));
            }
            // check bottom right
            if(row && (col+2)%8 &&
                (board[col+1][row-1] == omen || board[col+1][row-1] == oking) &&
                !board[col+2][row-1] &&
                (down || board[col][row] == king))
            {
                moves.push_back(Move(col,row,col+1,row-1,col+2,row-1,true,this));
            }
            // check top left
            if(col && (row+1)%4 &&
                (board[col-1][row] == omen || board[col-1][row] == oking) &&
                !board[col-2][row+1] &&
                (up || board[col][row] == king))
            {
                moves.push_back(Move(col,row,col-1,row,col-2,row+1,true,this));
            }
            //check bottom left
            if(col && row &&
                (board[col-1][row-1] == omen || board[col-1][row-1] == oking) &&
                !board[col-2][row-1] &&
                (down || board[col][row] == king)) 
            {
                moves.push_back(Move(col,row,col-1,row-1,col-2,row-1,true,this));
            }
        }
        else { // odd columns (right side)
            // check bottom right
            if ((col+1)%8 && row &&
                (board[col+1][row] == omen || board[col+1][row] == oking) &&
                !board[col+2][row-1] &&
                (down || board[col][row] == king))
            {
                moves.push_back(Move(col,row,col+1,row,col+2,row-1,true,this));
            }
            // check top right
            if ((col+1)%8 && (row+1)%4 &&
                (board[col+1][row+1] == omen || board[col+1][row+1] == oking) &&
                !board[col+2][row+1] &&
                (up || board[col][row] == king)) 
            {
                moves.push_back(Move(col,row,col+1,row+1,col+2,row+1,true,this));
            }
            // check bottom left
            if (row && col-1 &&
                (board[col-1][row] == omen || board[col-1][row] == oking) &&
                !board[col-2][row-1] &&
                (down || board[col][row] == king)) 
            {
                moves.push_back(Move(col,row,col-1,row,col-2,row-1,true,this));
            }
            //check top left
            if ((row+1)%4 && col-1 &&
                (board[col-1][row+1] == omen || board[col-1][row+1] == oking) &&
                !board[col-2][row+1] &&
                (up || board[col][row] == king)) 
            {
                moves.push_back(Move(col,row,col-1,row+1,col-2,row+1,true,this));
            }
        }
    }
    if (moves.size()) return true;
    return false;
}

void Board::terminalJumps(Player *p, std::vector<Move> &moves){
    for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        if (it->board->jumpsFrom(p,it->end[0],it->end[1],it->nextMoves)){
            moves.erase(it);
            it->board->jumpsFrom(p,it->end[0],it->end[1],moves);
            this->terminalJumps(p,moves);
            break;
        }
    }
}

void Board::legalMoves(Player *p, std::vector<Move> &moves) {
    if(!checkJumps(p,moves))
        checkMoves(p,moves);
    return;
}

void Board::makeMove(int start[], int middle[], int end[], bool isJump) {
    board[end[0]][end[1]] = board[start[0]][start[1]];
    board[start[0]][start[1]] = 0;
    if (isJump){
        board[end[0]][end[1]] = board[start[0]][start[1]];
        board[start[0]][start[1]] = 0;
        board[middle[0]][start[0]] = 0;
    }

}

void Board::kingMe(int col, int row){
    if (col%2){
        if(row == 3 && board[col][row] == 1)
            board[col][row] = 2;
    }
    else if(row == 0 && board[col][row] == 3){
        board[col][row] = 4;
    }
}

void Board::makeMove(Move* move) {
    if (move->isJump){
        this->copyBoard(move->board);
    }
    else {
        board[move->end[0]][move->end[1]] = board[move->start[0]][move->start[1]];
        board[move->start[0]][move->start[1]] = 0;
    }
    this->kingMe(move->end[0],move->end[1]);
}

void Board::makeSingleMove(Move* move) {
    if (move->isJump){
        board[move->end[0]][move->end[1]] = board[move->start[0]][move->start[1]];
        board[move->start[0]][move->start[1]] = 0;
        board[move->middle[0]][move->middle[1]] = 0;
        //this->copyBoard(move->board);
    }
    else {
        board[move->end[0]][move->end[1]] = board[move->start[0]][move->start[1]];
        board[move->start[0]][move->start[1]] = 0;
    }
    this->kingMe(move->end[0],move->end[1]);
}

const char* Board::uniPiece(int piece) {
    switch(piece) {
        case 0://empty
            return "\u00B7";
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

void Board::copyBoard(Board* src){
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 8; col++){
            this->board[col][row] = src->board[col][row];
        }
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
            std::cout << blank << " " << uniPiece(board[col][row]); 
        }
        std::cout << " " << rowID-- << std::endl << rowID;
        for (col = 0; col < 8; col+=2) {
            std::cout << " " << uniPiece(board[col][row]) << blank;
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

void Board::readBoard() {
    std::string infile;
    std::string line;
    char c;
    std::cout << "do you want to read in a file? (filename/n) \n";
    std::cin >> infile;
    if (!infile.compare("n"))
        return;
    std::cout << "opening " << infile << std::endl;

    std::ifstream ifh(infile,std::ifstream::in);

    int r = 4;
    for(int i = 0; i < 8; i++ ) {
        if (!(i%2)){
            r--;
        }
        for(int j = 0; j < 5; j++) {
            if (ifh.get(c)){
                if (c == '\n')
                    break;
                if(!(i%2)){ // even line
                    this->board[j*2+1][r] = c-48;
                }
                else {
                    this->board[j*2][r] = c-48;
                }
            }
            else {
                std::cout << "ERROR: your file has too few characters";
                exit(1);
            }
        }
    }

}