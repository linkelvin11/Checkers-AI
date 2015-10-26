#include "game.h"
#include "globals.h"


Game::Game(){
    board = new Board();
}

Game::~Game(){
    delete board;
}

void Game::play(){
    auto start = std::chrono::high_resolution_clock::now();
    // //float epoch = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    // std::cout<<"elapsed: "<<elapsed.count()<<std::endl;
    
    // // epoch = epoch/1e9;
    // // std::cout<<"time since epoch: "<<epoch/3600/24/365<<std::endl;
    // return;


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
    if (firstAI || secondAI)
    {
        std::cout<<"what is the AI time limit? (float seconds)\n";
        std::cin>>timeLimit;
        timeLimit = timeLimit * (0.49 * 1e9);
        std::cout<<"The time limit is "<<timeLimit<<".\n";
    }
    

    Player* first = new Player(true,firstAI);
    Player* second = new Player(false,secondAI);
    Player* currentPlayer = first;
    Player* opponent = second;
    board->init();
    board->readBoard();
    

    float elapsed_time;
    double timenow;

    while(true){
        ++moveCtr%2?currentPlayer = first:currentPlayer = second;
        moveCtr%2?opponent = second:opponent = first;
        std::cout<<"current move: "<<moveCtr<<std::endl;
        if (!board->legalMoves(currentPlayer,moves)){
            board->displayBoard();
            std::string loser;
            currentPlayer == first? loser = "black": loser = "white";
            std::cout << "game over. " << loser << " loses. You played for "<<moveCtr<<" turns.\n";
            return;
        }

        if (currentPlayer->isComputer){
            board->displayBoard();
            if (currentPlayer == first){
                if (moves[0].isJump){
                    board->terminalJumps(currentPlayer,moves);
                }
                Move* bestmove;
                start = std::chrono::high_resolution_clock::now();
                returnTime = timeLimit + std::chrono::high_resolution_clock::now().time_since_epoch().count();
                // std::cout<<"return time: "<<returnTime<<std::endl;
                // timenow = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                // std::cout<<"time now: "<<timenow<<std::endl;
                // std::cout<<"diff: "<<returnTime-timenow<<std::endl;
                for (int maxdepth = 1; maxdepth < 20; maxdepth++){
                    bestmove = this->alphaBeta_init(currentPlayer,opponent,maxdepth);
                    if (std::chrono::high_resolution_clock::now().time_since_epoch().count() > returnTime){
                        std::cout<<"searched to depth: "<<maxdepth<<std::endl;
                        break;
                    }
                }

                elapsed_time = (std::chrono::high_resolution_clock::now() - start).count();
                std::cout<<"time elapsed: "<<elapsed_time<<std::endl;
                elapsed_time = elapsed_time/1e9;
                

                if (elapsed_time < sleeptime/1e6){
                    usleep(floor((sleeptime/1e6-elapsed_time)*1e6));
                }

                board->makeMove(bestmove);
                //std::cout<<"Cleaning search tree\n";
                moves.erase(moves.begin(),moves.end());
                continue;
            }
            moveNumber = rand() % moves.size();
            usleep(sleeptime);
        }
        else for (moveNumber = 1000; moveNumber >= moves.size();) {
            board->displayBoard();
            printMoves();
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
                do {
                    std::cout << "You just jumped! Jump again!\n";
                    std::cin >> moveNumber;
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

Move* Game::alphaBeta_init(Player *maxplayer, Player *minplayer, int maxdepth){
    Move* bestmove = &moves[0];
    int v = INT_MIN;
    int alpha = INT_MIN;
    for(std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        v = board->alphaBeta(maxplayer,minplayer,maxplayer,INT_MIN,INT_MAX,maxdepth-1,&*it,false);
        if (v > alpha){
            alpha = v;
            bestmove = &*it;
        }
    }
    return bestmove;
}

int main() {

    Game g;

    g.play();

    return 0;
}
