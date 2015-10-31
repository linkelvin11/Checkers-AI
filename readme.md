##Overview

This project was completed in partial requirement for ECE469 Artificial Intelligence at The Cooper Union. The goal of this project is to design an artificial intelligence for checkers using the minimax algorithm for alternate moves. This algorithm is further improved on with the application of alpha-beta pruning.

<!-- MarkdownTOC -->

- [How to Play](#how-to-play)
	- [Starting the game](#starting-the-game)
	- [Specifying an Opening Board Position](#specifying-an-opening-board-position)
	- [Playing the Game](#playing-the-game)

<!-- /MarkdownTOC -->


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

The board consists of 8 columns and 8 rows, each numbered 1-7. When it is a human player's turn, multiple moves will be listed. These moves have the format `(startcol,startrow),(endcol,endrow)`.  Type in the number of the move you'd like to apply and the game will process the move accordingly.

In the case of multiple jumps, the game will prompt you for each segment of the jump. Enter the moves in the same manner.
