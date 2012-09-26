//
//  UserInteraction.c
//  PointerPlayground
//
//  Created by Yating Sheng on 12/15/11.
//  Copyright 2011 University of Michigan . All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "UserInteraction.h"
#include "GameBoard.h"

void clearInputStream() { while ('\n' != getchar()) {} }

int getIntegerFromUser()
{
	int i;
	scanf("%d", &i);
	clearInputStream();
	return i;
}

char getCharFromUser()
{
	char i = getchar();
	clearInputStream();
	return i;
}

void printOrListOfCharacters(char* characters)
{
	int numberOfCharacters = (int)strlen(characters);
	
	printf("%c", characters[0]);
	
	for (int i = 1; i < numberOfCharacters-1; ++i) 
		printf(", %c", characters[i]);
	
	printf(" or %c", characters[numberOfCharacters-1]);
}

bool stringContainsCharacter(char* str, char c)
{
	while (*str != '\0' && *str != c)
		++str;
	return (*str == c);
/*
	 for (int i = 0; i < strlen(str); ++i)
	 {
		if (str[i] == c)
			return true;
	 }
	return false;
*/
}

char gameGetInput(char* characters)
{
    char input;
	while (!stringContainsCharacter(characters, input = getCharFromUser()))
	{
		printf("It must be ");
		printOrListOfCharacters(characters);
		printf(".\n");
	}

	return input;
}

bool gameGetYesOrNo()
{
	return ('y' == gameGetInput("yn"));
}

// Dont know where is wrong in this code. Is it about pointers? Or is it about char / int?
// Why does it print twice "The address is not valid"?
void gameAskUserForLocation(int* row, int* col)
{   
    while (!indexIsValid(*row = getchar() - 'A') ||
		   !indexIsValid(*col = getIntegerFromUser() - 1))
    {
		printDialog(DialogMessageNotRealLocation);
    }
}

int gameUserInputNumber() 
{   
    int number;
    while (!indexIsValid(number = getIntegerFromUser() - 1)) 
		printDialog(DialogMessageWhatNumber);
    return number;
}

void printDialog(DialogMessage dialog)
{
    switch (dialog)
	{
        case DialogMessageSetOrDelete:
			printf("Would you like to set (s) or delete (d) a number?\n");
            break;
		case DialogMessageWhichLocation:
			printf("Which location?\n");
			break;
		case DialogMessageReplaceANumberOrNot:
			printf("There is already a number there. Do you want to replace it?\n");
			break;
		case DialogMessageNotRealLocation:
			printf("That location is not real.\n");
			break;
		case DialogMessageWhatNumber:
			printf("What number? Please enter a number from 1 to 9: ");
			break;
		case DialogMessagePermanentPosition:
			printf("That location is permanent, sorry.\n");
			break;
		case DialogMessageNoNumber:
			printf("There is no number there.\n");
			break;
		case DialogMessageCannotPutThere:
			printf("You can't put that number there.\n");
			break;
		case DialogMessageWon:
			printf("You must have cheated!\nSee you next time!\n");
			break;
        default:
            break;
    }

}
