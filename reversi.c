#include "reversi.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	menu();
	return EXIT_SUCCESS;
}

/*Function to create the inital menu*/
void menu()
{
	int x = 0;
	printf("\n\033[5m\033[96mWelcome to Reversi!\033[0m\033[39m\n");
	for(x = 0; x < 20; x++)	
	printf("=");
	printf("\nSelect an option:\n1. Play a game");
	printf("\n2. Quit the program\nPlease enter your choice:\n");
	choice();
}

/*Function that accepts the input, and sends the user
 * to either play game if 1 is selected, or quits if 
 * 2 is selected
*/
void choice()
{
	Player p1;
	Player p2;
	int x = 0;
	int xX = 0;
	char input[2];
	char *pInput;
	Player *temp;
	Boolean buffer = FALSE;
	
	fgets(input, 2, stdin);
/*This loop checks for a new line character!
 * if one is not found, the buffer is 
 * overloaded and it flushes using readRestOfLine
 * */						
	for(xX = 0; xX < 2; xX++)
	{
		if(input[xX] == '\n')
			buffer = TRUE;
	}
		
	if(buffer == FALSE)
		readRestOfLine();		

/*if the first input is digit, it creates a token
 * and then changes it to int
 * */		
	if(isdigit(input[0]))
	{	
	pInput = strtok(input, "\n");
	x = strtol(input, &pInput, 0);
		if(x != 1 && x != 2)
		{
			printf(COLOR_YELLOW"\nInvalid character input! please try again.\n"COLOR_RESET);
			menu();
		}
	
		else if(x == 1)
		{	
			/*runs the playGame function, if it returns NULL, it implies a
 * 			  draw and prints draw, otherwise it prints the winner */
			
			temp = playGame(&p1, &p2);
			
			if(temp == NULL)	
				printf(COLOR_YELLOW"\n D R A W \n"COLOR_RESET);
			else if(temp->token == RED)
				printf(COLOR_RED"\n R E D  W I N S \n"COLOR_RESET);
			else if (temp->token == CYAN)
				printf(COLOR_CYAN"\n C Y A N  W I N S \n"COLOR_RESET);
			
			menu();
				
			
		}
		else if(x == 2) 
		{	
			/* quits the game when the user wants!  */
			printf(COLOR_YELLOW"\nThank you for playing!\n"COLOR_RESET);	
			exit(0);
		}	
		else
		{
			/* if the int is too large, it reloops! */
			printf(COLOR_YELLOW"\nInvalid character input! please try again.\n"COLOR_RESET);
			menu();
		}
	}
	
	else
		/*if the input is not correct, it reloops*/
		{
			printf(COLOR_YELLOW"\nInvalid character input! please try again.\n"COLOR_RESET);
			menu();
		}


}

