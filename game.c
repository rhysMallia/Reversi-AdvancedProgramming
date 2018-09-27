#include "game.h"

Player * playGame(Player * first, Player * second)
{
	Player *pPlayer;
	Player *sPlayer;
	Boolean checker = FALSE;
	/* creating board */
	Cell board[BOARD_WIDTH][BOARD_HEIGHT];	
	/* assigning all the proper settings to board */
	initBoard(board);
	/* Creates random gen seed using the system time */
	srand(time(NULL));
	
	/*creating the players! */
	initFirstPlayer(first);
	initSecondPlayer(second, first->token);
	
	/* finds which token is red, and sets that player to be the first */
	if(first->token == RED)
	{
		pPlayer = first;
		sPlayer = second;
	}
	else
	{
		pPlayer = second;
		sPlayer = first;
	}

	/* Game loop! Checker is used to end the game if the board is full */
	while(!checker)
	{
		/*displays the board at the beginning of each round */
		displayBoard(board, first, second);
		/*checking if there is spots left on board, returns false if not */
		if(spotsLeft(board) == TRUE)
		{
			/* runs makeMove, make move returns false if you press enter! */
			if(makeMove(pPlayer, board) == FALSE)
			{
				int x = gameScore(board, CYAN);
				int y = gameScore(board, RED); 
				/* printing the final scores to the screen, and returning NULL if draw, or the winning player */
				printf(COLOR_YELLOW"\nF I N A L  S C O R E\n");
				printf("= = = = = = = = = = \n"COLOR_RESET);
				printf(COLOR_RED"%s Score = %d"COLOR_RESET, first->name, y);
				printf(COLOR_CYAN"\n%s Score = %d"COLOR_RESET, second->name,x);
				printf(COLOR_YELLOW"\n= = = = = = = = = = \n"COLOR_RESET);
				if(x > y)
					return second;
				else if(y > x)
					return first;
				else
					return NULL;		
			}
			/* Swaps the players pointers to put back into the make move function */
			swapPlayers(&pPlayer, &sPlayer);
		}
		else
			checker = TRUE;

	}	
	
	

	return NULL;
}


Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int column = 0;
	int row = 0;
	int xX = 0;
	int tempScore;
	Boolean check = FALSE;
	Boolean buffer = FALSE;
	Boolean checkInput = FALSE;
	char input[4];
	char *pInput;
	
	/*First loop to check if the move is valid! */
	while(checkInput == FALSE)
	{
		/* Second loop to check that the users input is correct */
		while(check == FALSE)
		{
			
			tempScore = gameScore(board,player->token);	
			/* prints the prompt for input depending on color, purely for looks :^] */
			if(player->token == RED)
			{
				printf(COLOR_RED "\n%sS C O R E - %d\n" COLOR_RESET,player->name,tempScore);
				printf("Please make a move in the format x,y (Column, Row): ");
			}
			else
			{
				printf(COLOR_CYAN "\n%sS C O R E - %d\n" COLOR_RESET, player->name, tempScore); 
				printf("please make a move in the format x,y (Column, Row): ");
			}
			
			
			fgets(input, 4, stdin);
					
			/* System to check if the buffer has overflowed! */		
			for(xX = 0; xX < 4; xX++)
			{
				if(input[xX] == '\n')
				buffer = TRUE;
			}
		
			if(!buffer)
				readRestOfLine();		

			/* if the user hits enter, this method returns false and the above methods will make it end the game ect */
			if(input[0] == '\n')
			{
				return FALSE;
			}
		
			/* Checks if the input is correct form, if so it breaks the loop */
			if(isdigit(input[0]) && isdigit(input[2]) && input[1] == ',')
				check = TRUE;
		}	
		
		/* splits the string up into two things, and then grabs the int from them and puts it through to the apply move */
		pInput = strtok(input, ",");
		row = strtol(input, &pInput, 0);
		pInput = strtok(NULL, "");
		column = strtol(pInput, &pInput, 0);
		
		/* Checks if the move is valid on the board */
		if(applyMove(board, column - 1, row - 1, player->token) == TRUE)
			checkInput = TRUE;
		else
		{
			printf(COLOR_YELLOW"\nInvalid move, please try again!\n"COLOR_RESET);
			check = FALSE;
		}
	}
	return TRUE;
}


Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{	
	Boolean checker = FALSE;
	Boolean checker1 = FALSE;
	Boolean checker2 = FALSE;

	/* Checks if there is already a piece on that location */
	if(board[y][x] == CYAN || board[y][x] == RED)
	{	
		printf(COLOR_YELLOW "Piece already in location, please try again!\n" COLOR_RESET );
		return FALSE;
	}
	if(x < 0 || y < 0)
	{
		printf(COLOR_YELLOW "Position out of range, please try again!\n" COLOR_RESET );
		return FALSE;
	}
	/* these checkers check the logic functions to see if they successfully were placed anywhere */
	checker = checkLogicNorth(board,y,x,token);
	checker1 = checkLogicCentre(board,y,x,token);
	checker2 = checkLogicSouth(board,y,x,token);
	
	/* if a piece is successfully changed, it changes itself because i miscoded the functions below!
 * 	   If no piece was placed, then the move is 'invalid' and false is returned */
	if(checker == TRUE || checker1 == TRUE || checker2 == TRUE)
	{
		board[y][x] = token;
		return TRUE;
	}
	return FALSE;
}

	
Boolean checkLogicNorth(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{
	int xX,yY,vV,zZ; 			
	int checkForPlacement = 0;	
	
/* These loops each check a direction, I won't comment on all of them but they all work on the same principle, 
 * each direction is initally either a minus/plus Y or X according to direction, which is shown by xX or yY.
 * If a BLANK is found, the loop quits and continues onto the next check, if a token of opposite color is found, the loop continues,
 * if a token is found of your own color, the loop will either quit (if it is a spot directly opposite) or will begin the next loop that
 * will continue backwards and changes all the tokens inbetween to the players color
 *
 * Also, the checkForPlacement increases when a token is placed, this is a rough move validation and works in the above function to tell
 * if a token is placed
 *
 * */
	/*North Western check*/
	
if(y != 0 && x != 0)
{
	for(yY=1,xX=1; yY <= y && xX <= (x); yY++, xX++)
	{
		if(board[y-yY][x-xX] == token && yY > 1)
		{
			for(vV=yY,zZ=xX; zZ>0&&vV>0; vV--, zZ--)
			{	
				board[(y-vV)][(x-zZ)] = token;
				checkForPlacement++;
			}
		}
		if(board[y-yY][x-xX] == BLANK)
			break;
	}
}	

	/*Northern check loop!*/
if(y != 0)
{
	for(yY=1; yY <= y; yY++)
	{	
		if(board[y-yY][x] == token && yY > 1)
		{	
			for(vV = yY; vV > 0; vV--)
			{
				board[(y-vV)][x] = token;
				checkForPlacement++;
			}
		}
		else if(board[y-yY][x] == BLANK)
			break;
	}
}	
	/*North eastern check loop! */
if(y != 0 && x != 7)
{ 
	for(yY=1, xX=1; yY <= y && xX <= (BOARD_HEIGHT - x); yY++,xX++)
	{
		if(board[y-yY][x+xX] == token && yY > 1)
		{
			for(vV=yY,zZ=xX;vV>0&&zZ>0;vV--,zZ--)
			{	
				board[(y-vV)][(x+zZ)] = token;
				checkForPlacement++;
			}
		}
		if(board[y-yY][x+xX] == BLANK)
			break;	
	}
	
}
	if(checkForPlacement > 0)
		return TRUE;
	else
		return FALSE;
}

Boolean checkLogicCentre(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{
	int xX,zZ;
	int checkForPlacement = 0;
	
	/*Western Check*/
if(x != 0)
{
	for(xX=1; xX <= x; xX++)
	{	
		if(board[y][x-xX] == token && xX > 1)
		{
			for(zZ = xX; zZ>0; zZ--)
			{
				board[y][x-zZ] = token;
				checkForPlacement++;
			}
		}
		if(board[y][x-xX] == BLANK)
			break;
	}
}	
	/*Eastern Check*/
if(x != 7)
{
	for(xX=1; x <= (BOARD_WIDTH - x); xX++)
	{
		if(board[y][x+xX] == token && xX > 1)
		{
			for(zZ = xX; zZ>0; zZ--)
			{
				board[y][x+zZ] = token;
				checkForPlacement++;
			}
				
		}
		if(board[y][x+xX] == BLANK)
			break;
	}
}

	if(checkForPlacement > 0)
		return TRUE;
	else
		return FALSE;

}

Boolean checkLogicSouth(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{
	int xX,yY,vV,zZ; 
	int checkForPlacement = 0;
		
	/*South Western check loop!*/
if(y != 7 && x != 0)
{
	for(yY=1,xX=1; yY <= (BOARD_WIDTH - y)&& xX <= (x); yY++, xX++)
	{
		if(board[y+yY][x-xX] == token && yY > 1)
		{ 
			for(vV=yY,zZ=xX; vV>0&&zZ>0; vV--, zZ--)
			{
				board[(y+zZ)][(x-vV)] = token;
				checkForPlacement++;
			}
		}
		if(board[y+yY][x-xX] == BLANK)
			break;
	}
}	

	/*Southern check loop!*/
if(y != 7)
{
	for(yY=1; yY <= (BOARD_WIDTH - y); yY++)
	{
		if(board[y+yY][x] == token && yY > 1)
		{	
			for(vV = yY; vV > 0; vV--)
			{
				board[(y+vV)][x] = token;
				checkForPlacement++;
			}
		}
		if(board[y+yY][x] == BLANK)
			break;
	}
}	

	/*South Eastern check loop! */
if(y != 7 && x != 7)
{
	for(yY=1, xX=1; yY <= (BOARD_WIDTH - y) && xX <= (BOARD_HEIGHT - x); yY++,xX++)
	{
		if(board[y+yY][x+xX] == token && yY > 1)
		{
			for(vV=yY,zZ=xX;vV>0&&zZ>0;vV--,zZ--)
			{
				board[(y+vV)][(x+zZ)] = token;
				checkForPlacement++;
			}
		}
		else if(board[y+yY][x+xX] == BLANK)
			break;	
	}
}
	
	if(checkForPlacement > 0)
		return TRUE;
	else
		return FALSE;
}

/* Checks through the whole loop and finds toekens of your own colour, before returning it */
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int score = 0;
	int x,y;
	
	for( x = 0; x < BOARD_HEIGHT; x++)
	{
		for( y = 0; y < BOARD_WIDTH; y++)
		{	
			if(board[x][y] == token)
				score++;
		}
	}
	return score;
}
	
/* swaps the players around */
void swapPlayers(Player ** first, Player ** second)
{
	Player *pTemp;
	
	pTemp = *first;
	*first = *second;
	*second = pTemp;
}
