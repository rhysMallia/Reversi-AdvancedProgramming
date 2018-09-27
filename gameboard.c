#include "gameboard.h"

/**
 * creates the board and assigns everything to be blank,
 * and then sets the beginning pieces to the right 
 * colours */
void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int x = 0;
	int y = 0;
	
	for(x = 0; x < BOARD_HEIGHT; x++)
	{
		for(y = 0; y < BOARD_WIDTH; y++)
		{
			board[x][y] = BLANK;
		}
	}	
	
	board[3][3] = RED;
	board[3][4] = CYAN;	
	board[4][3] = CYAN;
	board[4][4] = RED;
	
}

/**
 * Displays the board
 * */
void displayBoard(
    Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second)
{
	int x = 0;
	int y = 0;
	int z = 0;
	int v = 0;
	int u = 0;
	int counter = 1;
	
	printf("\n    1   2   3   4   5   6   7   8    \n");
	for(x = 0; x < 35; x++)
		printf("=");
	printf("\n");

	for(y = 0; y < 8; y++)
	{
		printf("%d |", counter);
		for(z = 0; z < 8; z++)
		{	
			if(board[y][z] == RED)
				printf(" " COLOR_RED "O" COLOR_RESET " |");
			else if (board[y][z] == CYAN)
				printf(" " COLOR_CYAN "O" COLOR_RESET " |");
			else
				printf("   |");
		}
		printf("\n");
		for(v = 0; v < 35; v++)
			if( y < 7)
				printf("-");
		if(y < 7)
			printf("\n");
		counter++;
	}
	for(u = 0; u < 35; u++)
		printf("=");

}

/* This function scans the array, and returns false if 
 * no blank spaces are remaining, thus it is a end game
 * */
Boolean spotsLeft(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{	
	int x = 0;
	int y = 0;
	
	for(x = 0; x < BOARD_HEIGHT; x++)
	{
		for(y = 0; y < BOARD_WIDTH; y++)
		{
			if(board[x][y] == BLANK)
				return TRUE;
		}
	}		
	
	return FALSE;
}



