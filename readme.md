##Overview

This project was completed in partial requirement for ECE469 Artificial Intelligence at The Cooper Union. The goal of this project is to design an artificial intelligence for checkers using the minimax algorithm for alternate moves. This algorithm is further improved on with the application of alpha-beta pruning.

## Build

```
git clone https://github.com/linkelvin11/Checkers-AI.git checkers;
cd checkers;
make;
./checkers.exe;
```


<!-- MarkdownTOC -->

- [System Requirements](#system-requirements)
- [How to Play](#how-to-play)
	- [Starting the game](#starting-the-game)
	- [Specifying an Opening Board Position](#specifying-an-opening-board-position)
	- [Playing the Game](#playing-the-game)
- [How it works](#how-it-works)
	- [Move Data Structure and Legal Moves](#move-data-structure-and-legal-moves)
	- [Iterative Deepening Search with Alpha-Beta Pruning](#iterative-deepening-search-with-alpha-beta-pruning)
	- [Heuristic Function](#heuristic-function)
- [References](#references)

<!-- /MarkdownTOC -->

## System Requirements

This program requires to following to build and play:

* g++ with support for std=c++11
* A linux system with a terminal that supports both utf-8 encoding and rendering of ANSI/VT100 escape sequences

## How to Play

### Starting the game

To start the game, simply follow the prompts the program gives. You can also choose to direct a file to stdin with the game configuration already set. 

The prompts given to start the game are as follows:

```
Is black a computer?
	Is black a smart computer?
Is white a computer?
	Is white a smart computer?
What is the computer time limit?
Would you like to read in a file?
```

An example input file is given below:
```
y
n
y
y
0.01
n
```
This configuration will set both players to computers with black using a simple heuristic and white using a more complex one. The time limit is set to 0.01 seconds, and there is no starting board position provided.

### Specifying an Opening Board Position

This checkers program allows for the functionality of inputting an initial board state. The input files must be 8 lines long with 4 characters on each line. These characters must all be numbers and follow this key:

```
empty 		= 0
black piece = 1
black king	= 2
white piece = 3
white king	= 4
```
An example input file is given below. Each line represents a row on the checkerboard.

```
0000
0000
0220
0000
0000
0330
0000
4111
```
### Playing the Game

The board consists of 8 columns and 8 rows, each numbered 0-7. When it is a human player's turn, multiple moves will be listed. These moves have the format `(startcol,startrow),(endcol,endrow)`.  Type in the number of the move you'd like to apply and the game will process the move accordingly.

In the case of multiple jumps, the game will prompt you for each segment of the jump. Enter the moves in the same manner.

## How it works

### Move Data Structure and Legal Moves

The current board state is stored as an 8x4 array.
As such, the legal moves function needs to search through the array for both jump and non-jump moves.
Since a player must take a jump move if possible, the legal moves function searches for jumps before moves, terminating if at least one jump is found.
The legal moves function takes an input vector to which it pushes Move data structres.

The Move data structure was designed with two things in mind: iterative deepening search and multiple-jump moves.
Because checkers moves can incorporate jumps which branch into several other possible jumps, the Move data structure has a member variable of type `std::vector<Move>` in order store possible branched jumps.
In addition, this vector is used when performing the iterative deepening search to store the moves for the next player.
This implementation allows the program to avoid rebuilding the search tree each time the search depth is increased.

In addition to storing a vector of possible moves, the Move data structure also stores the board state after the move has been applied to the previous board state.
This is implemented in the move's constructor which takes in the previous board state as an imput.
Storing each board state again allows the program to avoid rebuilding elements of the search tree which it has already traversed.

There are also considerations in the move data structure for the legal moves function.
Each move contains a bool called `isJump` which indicates whether or not to check for possible branched jumps.
The two conditions where isJump is false is when

1. the move is not a jump
2. the move is a jump, but involves a crowning

The storing of this variable is useful because multi-jump moves must be compressed into a single move for the AI to traverse.

### Iterative Deepening Search with Alpha-Beta Pruning

This AI utilizes iterative deepening search in conjunction with alpha beta pruning.
To generate the search tree, alpha beta function recursively applies the legal moves function to the nextMoves member variable of each of the current possible moves.
This process continues until the maximum depth is reached.
`std::vector<Move>` will automatically allocate enough memory to store the search tree.

The AI uses iterative deepening to first generate and search a low-depth tree and subsequently deepen and re-search the tree as long as there is time remaining.
Using iterative deepening ensures that the AI can play within a reasonable time constraint.
One drawback of this program's implementation of iterative deepening is that the search will take a small performance hit during the first couple of turns in the game as `std::vector<Move>` needs to reallocate memory to contain larger and larger trees with each increase in the search depth.
The upside is that `std::vector` does not free memory once it has been allocated, so even after the currentMoves vector has been cleared, there will not be a need to reallocate memory.

In addition to iterative deepening search, this AI utilizes alpha beta pruning.
Alpha beta pruning is a variation on the minimax algorithm which prevents the search from descending into sub-optimal subtrees.
Once the alpha beta pruning has determined one move to be worse than a previous move, it removes that subtree from the search, effectively reducing the number of nodes that need to be evaluated.
This is incredibly useful as the slowest part of the search is evaluating the legal moves function.
By pruning subtrees, the number of times the legal moves function needs to be evaluated is greatly reduced.

### Heuristic Function

The baseline heuristic function used is given in `Board::popCount()`.
It simply calculates difference in score between the current player and the opponent.
The score is evaluated by valuing men as 3 points and kings as 5 points.
In reality, any ratio of `n > 1` points for men and `2n-1` points for kings is going to be fairly effective, but testing showed that a ratio of 3/5 worked best.

To further improve on this heuristic, several values were added or subtracted in order to determine the AI's behavior when several moves return the same heuristic value.
This was implemented by scaling the baseline heuristic up by an integer value, and scaling the other parameters used by smaller integer values.
The other determining factors used in the heuristic are listed below in order of importance:

1. total distance of men from the king row
2. number of pieces left of the board (if losing)/ negative number of pieces left on the board (if winning)
3. the current position of the pieces on the board (prioritizes board edges)
4. a pseudorandom element to help break ties if all else fails

## References

* https://en.wikipedia.org/wiki/Draughts
* http://tim.hibal.org/blog/playing-checkers-with-minimax/