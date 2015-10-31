#include "globals.h"

unsigned int sleeptime = 500000;
double timeLimit = 0;
double returnTime = 0;
bool searchComplete = true;
int boardWeight[8][4] = {
	{4,4,4,4},
	{3,3,3,4},
	{4,2,2,3},
	{3,1,2,4},
	{4,2,1,3},
	{3,2,2,4},
	{4,3,3,3},
	{4,4,4,4},
};