/*
 *Nicola Quoziente
 *cis-170-01
 *Tic Tac Toe game
 */

//Make a game of tic tac toe.
//The grid will be a 2d int array that will hold a base value of 0. When a
//player uses the space it will be filled with either a 1 or a 2. This number
//will determine where which user has gone and if the space is available due to
//C's non-zero true value. To access a certain location in the grid, I'll follow
//the 'battleship' method of a letter/number grid (A1 = [1][1]).

// X = 1
// O = 2

#include <stdio.h>

//Make some prototypes
int askYN();
void displayBoard(int [3][3]);
char getLetter(int);
int * selectLoc(int [3][3]);
void setTurn(int *, int);
int checkForWin(int [3][3]);
int * runAI(int [3][3]);  //Prototype for the AI
void checkLine(int *, int *, int *, int **, int **);
	


int main() {
	//Display the rules to the user.
	printf("Welcome to Tic Tac Toe!\nHow to play:\n");
	printf("There are two players: player 1 is an 'X' and player 2 is an 'O'\n");
	printf("The goal of the game is to get three of your spaces in a row.\n");
	printf("To enter a position into the grid, use the format of\n");
	printf("[letter][number] to choose. For example, 'A1' would be the upper\n");
	printf("left corner of the grid and 'C3' would be the lower bottom corner.\n\n");
	
	
	//While the user wants to continue, start the game (again).
	do {
		//Make some vars
		int winner = 0;
		int grid[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		int enableAI = 0;
		
		//Ask the user if they want to go against the AI.
		printf("Do you want to go against the AI? ('y' or 'n')\n");
		enableAI = askYN();
		
		//There can only be nine rounds of the game before there are no more
		//spaces left to go to.
		for (int i = 0; i < 9; ++i) {
			//Make some vars
			int *gridPtr;
			
			//Show the grid to the players.
			displayBoard(grid);
			
			if ( enableAI && ((i % 2 + 1) == 2) ) {
				//Run the AI and get the pointer that it returns.
				gridPtr = runAI(grid);
			}
			else {
				//Ask the user what position they would like to mark.
				printf("Player %c: ", getLetter(i % 2 + 1));
				gridPtr = selectLoc(grid);
			
				//Make sure that the space is empty.
				while (*gridPtr) {
					printf("This space has already been used, please choose another.\n");
					printf("Player %c: ", getLetter(i % 2 + 1));
					gridPtr = selectLoc(grid);
				}
			}
			
			//Set the space in the grid to that player's value.
			setTurn(gridPtr, i % 2 + 1);
			
			//Check if any user has won yet.
			if (checkForWin(grid)) {
				break;
			}
		}
		
		//Display the grid back to the players so they see how things
		//worked out.
		displayBoard(grid);
		
		//Figure out who has won.
		winner = checkForWin(grid);
		if (winner) {
			printf("Player %c has won this game!\n", getLetter(winner));
		} else {
			printf("No one has won this game.\n");
		}
		
		//Ask if the players want to play again.
		printf("\nWould you like to play again? ('y' or 'n')\n");
	} while (askYN());
	
	
	//Say something dumb.
	printf("strange game. The only winning move is not to play.\nHow about a nice game of chess?\n");
	
	return 0;
}


//Ask the user if they would like to continue to play.
int askYN() {
	//Make a var to hold the answer.
	char ans;
	
	while (42) {
		//Get the answer from the user.
		scanf("\n%c", &ans);
		
		switch (ans) {
			case 'y':
			case 'Y':
				return 1;
				break;
			case 'n':
			case 'N':
				return 0;
				break;
			default:
				printf("Answer '%c' not recognized.\n", ans);
		}
	}
}

//Function to show the grid back to the user.
void displayBoard(int grid[3][3]) {
	//Display the grid to the user. I know tic tac toe is a 3x3 grid so I do not
	//need the size passed to the function.
	printf("\n\n  1   2   3 \n");
	
	for (int i = 0; i < 3; ++i) {
		//Print the letters seperated by pipes.
		printf(
			"%c %c | %c | %c \n",
			(65 + i),
			getLetter(grid[i][0]),
			getLetter(grid[i][1]),
			getLetter(grid[i][2])
		);
		
		//Make a line between the rows, but skip the last.
		if (i < 2) {
			printf(" -----------\n");
		}
	}
	printf("\n");
}


//Function to return the letter associated with the number.
char getLetter(int num) {
	// X = 1
	// O = 2
	
	switch (num) {
		case 1:
			return 'X';
			break;
		case 2:
			return 'O';
			break;
		default:
			return ' ';
	}
}


//Get a location from the user, and return the pointer of the grid's location
//back.
int * selectLoc(int grid[3][3]) {
	//Make some vars
	char locX;
	int locY;
	
	while (42) {
		//Get the answer from the user.
		scanf("\n%c", &locX);
		scanf("%d", &locY);
		
		switch (locX) {
			case 'a':
			case 'A':
				if (locY > 3 || locY < 1) {
					printf("Answer '%c%d' out of bounds.\nEnter location: ", locX, locY);
				} else {
					return &grid[0][locY - 1];
				}
				break;
			case 'b':
			case 'B':
				if (locY > 3 || locY < 1) {
					printf("Answer '%c%d' out of bounds.\nEnter location: ", locX, locY);
				} else {
					return &grid[1][locY - 1];
				}
				break;
			case 'c':
			case 'C':
				if (locY > 3 || locY < 1) {
					printf("Answer '%c%d' out of bounds.\nEnter location: ", locX, locY);
				} else {
					return &grid[2][locY - 1];
				}
				break;
			default:
				printf("Answer '%c%d' out of bounds.\nEnter location: ", locX, locY);
		}
	}
}


//Make a function to set a player's value to a location on the grid.
void setTurn(int *gridPtr, int player) {
	*gridPtr = player;
}


//Make a function that will check the grid and see if any user has won the game.
//Return the number of the user who won, or a zero if no one has.
int checkForWin(int grid[3][3]) {
	//Search through the array to check if anyone has won horozontally.
	for (int x = 0; x < 3; ++x) {
		if ( (grid[x][0] == grid[x][1]) && (grid[x][0] == grid[x][2]) ) {
			return grid[x][0];
		}
	}
	
	//Search through the array to check if anyone has won vertically.
	for (int y = 0; y < 3; ++y) {
		if ( (grid[0][y] == grid[1][y]) && (grid[0][y] == grid[2][y]) ) {
			return grid[0][y];
		}
	}
	
	//Check the diagonals of the grid
	if ( (grid[0][0] == grid[1][1]) && (grid[0][0] == grid[2][2]) ) {
		return grid[1][1];
	}
	else if ( (grid[0][2] == grid[1][1]) && (grid[2][0] == grid[1][1]) ) {
		return grid[1][1];
	}
	
	//Return 0 as the default if no match is found.
	return 0;
}


//Function for the AI.
int * runAI(int grid[3][3]) {
	//Make some vars
	int *defense = 0;
	int *offense = 0;
	
	//Show the AI is running and display progress by displaying a dot after each
	//step.
	printf("\nThinking.");
	
	//Check each possible direction. The logic of the AI should be to:
	//	1. Place a winning move if found.
	//	2. Block the player if they are going to win.
	//	3. Get a corner position if possible.
	//	4. Choose a misc spot.
	
	//Check the horozontal lines.
	for (int x = 0; x < 3; ++x) {
		//Check for an opening.
		checkLine(&grid[x][0], &grid[x][1], &grid[x][2], &offense, &defense);
	}
	//Check vertical lines.
	for (int y = 0; y < 3; ++y) {
		//Check for an opening.
		checkLine(&grid[0][y], &grid[1][y], &grid[2][y], &offense, &defense);
	}
	//Check horizontal lines.
	checkLine(&grid[0][0], &grid[1][1], &grid[2][2], &offense, &defense);
	checkLine(&grid[0][2], &grid[1][1], &grid[2][0], &offense, &defense);
	
	//Check if the offense or defense is found, and return it.
	if (offense != 0) {
		return offense;
	}
	else if (defense != 0) {
		return defense;
	}
	
	
	//If the program has made it this far, then choose a corner and
	//make sure that it is open.
	if (! grid[0][0]) {
		return &grid[0][0];
	}
	else if (! grid[2][2]) {
		return &grid[2][2];
	}
	else if (! grid[0][2]) {
		return &grid[0][2];
	}
	else if (! grid[2][0]) {
		return &grid[2][0];
	}
	
	
	//At this point, just choose something.
	for (int x = 0; x < 2; ++x) {
		for (int y = 0; y < 2; ++y) {
			if (! grid[x][y]) {
				return &grid[x][y];
			}
		}
	}
}


//Function to check for an interesting point on the line given.
void checkLine(int *p1, int *p2, int *p3, int **offence, int **defence) {
	//Make some vars
	int sum = *p1 + *p2 + *p3;
	
	//Determine if this line is interesting at all.
	if (sum == 4) {
		//If the sum of the line is 4, this means that there has to be
		//two spaces occupied by player 2. Due to the way this is writen,
		//the AI is always player two. This means that the AI can use
		//The blank spot on this line to win the game.
		
		//Find the empty space.
		int *emptySpace;
		int num = 0;
		if (! *p1) {
			emptySpace = p1;
			++num;
		}
		if (! *p2) {
			emptySpace = p2;
			++num;
		}
		if (! *p3) {
			emptySpace = p3;
			++num;
		}
		
		if (num == 1) {
			//This is an offensive move.
			*offence = emptySpace;
		}
	}
	else if (sum == 2) {
		//This one is less straight forward than the previous in that,
		//this can be player 1 about to win, or player 2 has made one
		//mark on this line.
		
		//Figure out how many empty spaces are on this line.
		int *emptySpace;
		int num = 0;
		if (! *p1) {
			emptySpace = p1;
			++num;
		}
		if (! *p2) {
			emptySpace = p2;
			++num;
		}
		if (! *p3) {
			emptySpace = p3;
			++num;
		}
		
		//If there is only one blank spot in the line, then go there.
		//Otherwise, just ignore it.
		if (num == 1) {
			//This is a defensive move.
			*defence = emptySpace;
		}
	}
	else {
		//This line is pretty uninteresting.
	}
	
	//Print out a dot to show progress to the user.
	printf(".");
}

