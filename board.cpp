
#include "board.h"  
#include <iostream>

Move::Move()
{
    start[0] = 0;
    start[1] = 0;
    end[0] = 0;
    end[1] = 0;
}

Move::Move(int startcol, int startrow, int endcol, int endrow)
{
    start[0] = startcol;
    start[1] = startrow;
    end[0] = endcol;
    end[1] = endrow;
}

Player::Player(bool first)
{
    if (first)
    {
        men = 1;
        king = 2;
        return;
    }
    men = 3;
    king = 4;
    return;
}

Board::Board()
{
    moves = new Move[32];
    return;
}

Board::~Board()
{
    delete[] moves;
    return;
}

void Board::init(Player *p)
{
    int row = 0;
    int col = 0;
    int pmen = p->men;
    int omen = p->men == 1 ? 3 : 1;
    for(col = 0; col < 8; col++)
    {
        this->b[col][0] = pmen;
        this->b[col][3] = omen;
    }
    for (col = 1; col < 8; col+=2)
    {
        this->b[col-1][1] = pmen;
        this->b[col][2] = omen;
    }
}

bool Board::checkMoves(int** board, Player *p)
{
    this->moveCtr = 0;
    for(int row = 0; row < 4; row++)// go through rows
    {
        for(int col = 0; col < 8; col++)// go through columns
        {
            if (board[col][row])
            {
                if (col % 2) // even columns (left side)
                {
                    if(!board[col+1][row])
                    {
                        this->moves[moveCtr++] = Move(col,row,col+1,row);
                    }
                    else {} //check jump
                    if((row+1)%4 && !board[col+1][row+1])
                    {
                        this->moves[moveCtr++] = Move(col,row,col+1,row+1);
                    }
                    else {} //check jump
                    if(col && !board[col-1][row])
                    {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    else {} //check jump
                    if(col && (row+1)%4 && !board[col-1][row+1])
                    {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    else {} //check jump

                }
                else // odd columns (right side)
                {
                    if ((col+1)%4 && !board[col+1][row])
                    {
                        this->moves[moveCtr++] = Move(col,row,col+1,row);
                    }
                    else {} //check jumps
                    if (row && (col+1)%4 && !board[col+1][row-1])
                    {
                        this->moves[moveCtr++] = Move(col,row,col+1,row-1);
                    }
                    if (!board[col-1][row])
                    {
                        this->moves[moveCtr++] = Move(col,row,col-1,row);
                    }
                    else {} //check jumps
                    if (row && !board[col-1][row-1])
                    {
                        this->moves[moveCtr++] = Move(col,row,col-1,row-1);
                    }
                    else {} //check jumps
                }
            }
        }
    }
    return true;
}
bool Board::checkJumps(int** board, Player *p)
{
    return true;
}

bool Board::legalMoves(int** board, Player *p)
{
    if (Board::checkJumps(board,p))
    {
        //list the legal jumps
        return true;
    }
    if (Board::checkMoves(board,p))
    {
        // list the legal moves
        return true;
    }
    return false;
}

int Board::makeMove(int start, int end, int** board)
{
    return 0;
}

const char* Board::uniPiece(int piece)
{
    switch(piece)
    {
        case 0://empty
            return "\u25A3";
        case 1://black piece
            return "\u25C9";
        case 2://black king
            return "\u265A";
        case 3://red piece
            return "\u25CE";
        case 4://red king
            return "\u2654";
    }
}

void Board::displayBoard()
{
    int row = 0;
    int col = 0;
    int colID = 0;
    int rowID = 7;
    std::cout << "  ";
    for(col = 0; col < 8; col++)
    {
        std::cout << colID++ << " ";
    }
    std::cout << std::endl;
    char blank[10] = " \u25FB";
    for(row = 3; row > -1; row--)
    {
        std::cout << rowID;
        for (col = 1; col < 8; col+=2)
        {
            std::cout << blank << " " << uniPiece(this->b[col][row]); 
        }
        std::cout << " " << rowID-- << std::endl << rowID;
        for (col = 0; col < 8; col+=2)
        {
            std::cout << " " << uniPiece(this->b[col][row]) << blank;
        }
        std::cout << " " << rowID-- << std::endl;
    }
    std::cout << "  ";
    for(col = 0, colID = 0; col < 8; col++)
    {
        std::cout << colID++ << " ";
    }
    std::cout << std::endl;
    return;
}

int main()
{
    system("Color 1A");
    Player* p = new Player(true);
    Board* b = new Board();
    b->init(p);
    b->displayBoard();
    return 0;
}