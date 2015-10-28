#include "game.h"
#include "globals.h"


Game::Game(){
    board = new Board();
}

Game::~Game(){
    delete board;
}

void Game::play(){
    srand(time(0));
    auto start = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    int moveCtr = 0;
    int moveNumber;
    int col;
    int row;
    int maxdepth = 0;
    float elapsed_time;
    double timenow;
    Player* first = new Player(true);
    Player* second = new Player(false);
    Player* currentPlayer = first;
    Player* opponent = second;

    // initialize players
    std::string initAI;
    std::cout<< "Is black a computer? (y/n)\n";
    std::cin>> initAI;
    if (initAI[0] == 'y'){
        first->isComputer = true;
        std::cout<<"Is black a smart computer?\n";
        std::cin>> initAI;
        if (initAI[0] == 'y'){
            first->isIntelligent = true;
        }
    }
    std::cout<< "Is white a computer? (y/n)\n";
    std::cin>> initAI;
    if (initAI[0] == 'y'){
        second->isComputer = true;
        std::cout<<"Is white a smart computer?\n";
        std::cin>> initAI;
        if (initAI[0] == 'y'){
            second->isIntelligent = true;
        }
    }
    if (first->isComputer || second->isComputer)
    {
        std::cout<<"what is the AI time limit? (float seconds)\n";
        std::cin>>timeLimit;
        timeLimit = timeLimit * (0.99 * 1e9);
        std::cout<<"The time limit is "<<timeLimit<<".\n";
    }

    board->init();
    board->readBoard();

    // start game
    while(true){
        // clear screen
        
        ++moveCtr%2?currentPlayer = first:currentPlayer = second;
        moveCtr%2?opponent = second:opponent = first;
        std::cout<<"current move: "<<moveCtr<<std::endl;

        // check for moves
        if (!board->legalMoves(currentPlayer,moves)){
            std::cout<<"\033[2J\033[1;1H";
            board->displayBoard();
            std::string loser;
            currentPlayer == first? loser = "black": loser = "white";
            std::cout << "game over. " << loser << " loses. You played for "<<moveCtr<<" turns.\n";
            return;
        }

        // computer's turn
        if (currentPlayer->isComputer){
            

            // find terminal jump moves
            if (moves[0].isJump){
                board->terminalJumps(currentPlayer,moves);
            }

            // iterative deepening search w/ alpha beta pruning
            Move* bestmove;
            Move* bestmove_tmp;
            searchComplete = true;
            start = std::chrono::high_resolution_clock::now();
            returnTime = timeLimit + std::chrono::high_resolution_clock::now().time_since_epoch().count();
            for (int depth = 1; depth < 20; depth++){
                bestmove_tmp = this->alphaBeta_init(currentPlayer,opponent,depth);
                if (searchComplete){
                    bestmove = bestmove_tmp;
                }
                else {
                    maxdepth = depth;
                    break;
                }
            }
            //bestmove = this->alphaBeta_init(currentPlayer,opponent,10);
            std::cout<<"\033[2J\033[1;1H";
            board->displayBoard();
            std::cout<<"searched to depth: "<<maxdepth<<std::endl;

            // print search time
            elapsed_time = (std::chrono::high_resolution_clock::now() - start).count();
            elapsed_time = elapsed_time/1e9;
            std::cout<<"search time: "<<elapsed_time<<std::endl;
            if (elapsed_time > timeLimit){
                std::cout<<"oops! went over the time limit\n";

            }
            // apply move
            board->makeMove(bestmove);
            //printMoves();
            moves.clear();
        }

        // human's turn
        else {
            // get player's move & apply it
            do{
                std::cout<<"\033[2J\033[1;1H";
                board->displayBoard();
                printMoves();
                std::cout << "type in which move you'd like\n";
                std::cin >> moveNumber;
            } while (moveNumber > moves.size());
            board->makeSingleMove(&moves[moveNumber]);

            // check if there is a multi-jump possibility
            if (moves[moveNumber].isJump) {
                col = moves[moveNumber].end[0];
                row = moves[moveNumber].end[1];
                moves.clear();
                // keep taking turns if you haven't finished jumping
                while (board->jumpsFrom(currentPlayer,col,row,moves)) {
                    do {
                        std::cout<<"\033[2J\033[1;1H";
                        std::cout<<"current move: "<<moveCtr<<std::endl;
                        board->displayBoard();
                        std::cout << "You just jumped! Jump again!\n";
                        printMoves();
                        std::cin >> moveNumber;
                    }
                    while (moveNumber >= moves.size());
                    board->makeSingleMove(&moves[moveNumber]);
                    col = moves[moveNumber].end[0];
                    row = moves[moveNumber].end[1];
                    moves.clear();
                }
            }
            else
                moves.clear();
        }
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
        v = it->board->alphaBeta(maxplayer,minplayer,maxplayer,INT_MIN,INT_MAX,maxdepth-1,&*it,false);
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
