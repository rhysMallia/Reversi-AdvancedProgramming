#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * creates the first player
 * */
void initFirstPlayer(Player * player)
{ 
	char input[10];
	int random = 0;
	int x;
	Boolean check = FALSE;
	Boolean loop = TRUE;	
	
	/* Prompts user to enter name, if a newline character is found in the first 
 *	   first spot, it reprompts! */

	while(loop == TRUE)
	{
		printf("\nPlayer 1, please enter your name!(up to 8 characters)\n");
		fgets(input, 10, stdin);	
		if(input[0] == '\n')
			printf(COLOR_YELLOW "\n Invalid input, please try again!" COLOR_RESET);
		else
			loop = FALSE;
	}
	
	/* same system to check if buffer has overflowed as in reversi */
	for(x = 0; x < 10; x++)
	{	
		if(input[x] == '\n')
			check = TRUE;
	}
	
	if(check == FALSE)
		readRestOfLine();

	strcpy(player->name, input);
	
	/* System to generate random seed, and assign color! */
	random = rand() % 2; 
	
	printf("Your colour will be ");
	if(random == 0)
	{
		player->token = RED;
		printf(COLOR_RED "RED\n" COLOR_RESET);
	}
	else
	{
		player->token = CYAN;
		printf(COLOR_CYAN "CYAN\n" COLOR_RESET);
	}

}

void initSecondPlayer(Player * player, Cell token)
{
	char input[10];
	int x;
	Boolean check = FALSE;
	Boolean loop = TRUE;	

	while(loop == TRUE)
	{
		printf("\nPlayer 2, please enter your name!(up to 8 characters)\n");
		fgets(input, 10, stdin);	
		if(input[0] == '\n')
			printf(COLOR_YELLOW "\n Invalid input, please try again!" COLOR_RESET); 
		else
			loop = FALSE;
	}
	
	for(x = 0; x < 10; x++)
	{	
		if(input[x] == '\n')
			check = TRUE;
	}
	
	if(check == FALSE)
		readRestOfLine();

	strcpy(player->name, input);
	
	/* Checks if above player is red, if not, assigns red! */
	printf("Your color will be ");
	if(token == RED)
	{
		player->token = CYAN;
		printf(COLOR_CYAN "CYAN\n" COLOR_RESET);
	}		
	else
	{
		player->token = RED;
		printf(COLOR_RED "RED\n" COLOR_RESET);
	}
}	
