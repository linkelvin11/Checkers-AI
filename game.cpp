#include "game.h"
#include "globals.h"


Game::Game(){
    board = new Board();
}

void Game::play(){
    int moveCtr = 0;
    int moveNumber;
    int col;
    int row;

    bool firstAI = false;
    bool secondAI = false;

    std::string initAI;
    std::cout<< "Is black a computer? (y/n)\n";
    std::cin>> initAI;
    if (initAI[0] == 'y')
        firstAI = true;
    std::cout<< "Is white a computer? (y/n)\n";
    std::cin>> initAI;
    if (initAI[0] == 'y')
        secondAI = true;
    // if (firstAI || secondAI)
    // {
    //     std::cout<<"what is the AI time limit? (float seconds)\n";
    //     std::cin>>timeLimit;
    //     returnTime = timeLimit * 0.99;
    //     //std::cout<<"The time limit is "<<timeLimit<<". The return time is "<<returnTime<<std::endl;
    // }
    auto start = std::chrono::high_resolution_clock::now();

    Player* first = new Player(true,firstAI);
    Player* second = new Player(false,secondAI);
    Player* currentPlayer = first;
    Player* opponent = second;
    board->init();
    board->readBoard();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout<<elapsed.count()<<std::endl;

    float elapsed_time;

    while(true){
        ++moveCtr%2?currentPlayer = first:currentPlayer = second;
        moveCtr%2?opponent = second:opponent = first;
        board->displayBoard();
        board->legalMoves(currentPlayer,moves);
        if (!currentPlayer->isComputer)printMoves();
        else usleep(sleeptime);
        if (moves.size() == 0)
        {
            std::string loser;
            currentPlayer == first? loser = "black": loser = "white";
            std::cout << "game over. " << loser << " loses.\n";
            return;
        }
        // if (board->checkJumps(currentPlayer,moves)){
        //     board->terminalJumps(currentPlayer,moves);
        //     printMoves();
        // }
        if (currentPlayer->isComputer){
            if (true){
                if (moves[0].isJump){
                    board->terminalJumps(currentPlayer,moves);
                }
                start = std::chrono::high_resolution_clock::now();
                this->alphaBeta_init(currentPlayer,opponent,10);
                elapsed_time = (std::chrono::high_resolution_clock::now() - start).count();
                elapsed_time = elapsed_time/1e9;
                

                if (elapsed_time < 0.5){
                    usleep(floor((0.5-elapsed_time)*1e6));
                }

                board->makeMove(&*(moves.end()-1));
                //std::cout<<"Cleaning search tree\n";
                moves.clear();
                std::cout<<"time elapsed: "<<elapsed_time<<std::endl;
                continue;
            }
            moveNumber = rand() % moves.size();
        }
        
        else for (moveNumber = 1000; moveNumber >= moves.size();) {
            std::cout << "type in which move you'd like\n";
            std::cin >> moveNumber;
        }
        //board->makeSingleMove(moves[moveNumber].start,moves[moveNumber].end,moves[moveNumber].isJump);
        board->makeSingleMove(&moves[moveNumber]);
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
                //board->makeSingleMove(moves[moveNumber].start,moves[moveNumber].end,moves[moveNumber].isJump);
                board->makeSingleMove(&moves[moveNumber]);
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

void Game::alphaBeta_init(Player *maxplayer, Player *minplayer, int maxdepth){
    std::vector<Move>::iterator bestmove = moves.begin();
    int v = INT_MIN;
    int alpha = INT_MIN;
    for(std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        v = board->alphaBeta(maxplayer,minplayer,maxplayer,INT_MIN,INT_MAX,maxdepth-1,&*it,false);
        if (v > alpha){
            alpha = v;
            bestmove = it;
        }
    }
    moves.insert(moves.end(),*bestmove);
}

int main() {

    Game g;

    g.play();

    return 0;
}
