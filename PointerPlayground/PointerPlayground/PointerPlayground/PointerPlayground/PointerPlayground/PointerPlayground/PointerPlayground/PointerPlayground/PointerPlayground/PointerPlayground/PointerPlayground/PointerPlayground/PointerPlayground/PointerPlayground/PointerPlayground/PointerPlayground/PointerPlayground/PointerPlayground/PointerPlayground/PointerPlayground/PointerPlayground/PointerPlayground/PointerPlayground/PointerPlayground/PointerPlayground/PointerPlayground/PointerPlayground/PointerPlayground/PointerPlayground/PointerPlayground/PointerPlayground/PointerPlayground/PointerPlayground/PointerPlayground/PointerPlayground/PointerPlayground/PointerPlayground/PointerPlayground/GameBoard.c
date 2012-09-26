//
//  GameBoard.c
//  PointerPlayground
//
//  Created by Yating Sheng on 12/13/11.
//  Copyright 2011 University of Michigan . All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "GameBoard.h"

bool indexIsValid(int index) { return (index >= 0 && index <= LINE_SIZE-1); }

char getCharFromFile(FILE* file)
{
	char c = getc(file);
	while (c != '_' && !indexIsValid(c-'1') && EOF != c)
	{
		c = getc(file);
	}
	return c;
}

bool gameBoardInitializeFromFile(GameBoard board, char* filename)
{
	FILE* pFile = fopen(filename, "r");
	if (NULL == pFile)
	{
		printf("Error opening the file."); //%s in mode %s.", filename, mode);
		return false;
	}
	
	char c = getCharFromFile(pFile);
	int i = 0;
	while (EOF != c && BOARD_SIZE != i)
	{
		int val = c-'1';
		if (indexIsValid(val))
		{
			board[i].value = val;
			board[i].permanent = true;
		}
		else if ('_' == c)
		{
			board[i].value = UNDERLINE_ELEMENT;
			board[i].permanent = false;
		}
		++i;
		c = getCharFromFile(pFile);
	}
	
	fclose(pFile);
	
	if (BOARD_SIZE > i)
	{
		printf("Incomplete board in file.\n");
		return false;
	}	
	return true;
}


/*
void gameBoardInitializeWithExample(GameBoard board)
{
	int values[] =
	{
#define _ (BLANK_ELEMENT)
		9, 4, _, _, 3, _, _, _, _,
		3, _, 8, 6, _, 1, 9, _, 5,
		_, 1, _, 4, _, 8, 3, 2, _,
		_, _, _, _, _, 7, _, 1, _,
		7, _, 1, _, _, _, 4, _, 3,
		_, 2, _, 5, _, _, _, _, _,
		_, 9, 4, 8, _, 3, _, 7, _,
		2, _, 5, 1, _, 9, 6, _, 4,
		_,_ , _, _, 6, _, _, 3, 9
#undef _
	};
	
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		int value = values[i];
		if (BLANK_ELEMENT != value)
			--value; // move values 1-9 to be 0-8
		
		int row = i / 9;
		int col = i % 9;
		
		gameBoardSetValue(board, row, col, value);
		gameBoardValueSetPermanent(board, row, col, (-1 != value));
	}
}
*/

void printDivider() { printf("  +-------------+-------------+-------------+\n"); }

void gameBoardSetValue(GameBoard board, int row, int column, int v)
{
    board[row*LINE_SIZE+column].value = v;
}

int gameBoardValue(GameBoard board, int row, int column)
{
    return board[row*LINE_SIZE+column].value;
} 

void gameBoardValueSetPermanent(GameBoard board, int row, int column, bool p)
{
	board[row*LINE_SIZE+column].permanent = p;
}

bool gameBoardValuePermanent(GameBoard board, int row, int column)
{
	return board[row*LINE_SIZE+column].permanent;
}

void gameBoardPrintValue(int value, bool permanent)
{
	switch (value) {
		case BLANK_ELEMENT:
			printf("    ");
			break;
		case UNDERLINE_ELEMENT:
			printf("  _ ");
			break;
		default:
			if (permanent)
				printf(" [%d]", value+1);
			else
				printf("  %d ", value+1);
			break;
	}	
}

void gameBoardPrintColumnGroup(GameBoard board, int row, int columnGroup)
{
	for (int l = 0; l < GROUP_SIZE; ++l)
	{
		int col = columnGroup * GROUP_SIZE + l;
		int value = gameBoardValue(board, row, col);
		bool permanent = gameBoardValuePermanent(board, row, col);
		gameBoardPrintValue(value, permanent);
	}
}

void gameBoardPrintRow(GameBoard board, int row)
{
	printf("%c |", 'A' + row);
	for (int k = 0; k < GROUP_SIZE; ++k) 
	{
		gameBoardPrintColumnGroup(board, row, k);
		printf(" |");
	}
}

void gameBoardPrintRowGroup(GameBoard board, int rowGroup)
{
	for (int j = 0; j < GROUP_SIZE; ++j) 
	{
		int row = rowGroup * GROUP_SIZE + j;
		gameBoardPrintRow(board, row);
		printf("\n");
	}
}

void gameBoardPrint(GameBoard board)
{
    printf("     1   2   3     4   5   6     7   8   9\n");
    printDivider();
    for (int i = 0; i < GROUP_SIZE; ++i)
    {
        gameBoardPrintRowGroup(board, i);
        printDivider();
    }
}

bool gameBoardRowAllowsValue(GameBoard board, int row, int value)
{
	for (int col = 0; col < LINE_SIZE; ++col)
	{
		if (gameBoardValue(board, row, col) == value)
			return false;
	}
	return true;
}

bool gameBoardColumnAllowsValue(GameBoard board, int col, int value)
{
	for (int row = 0; row < LINE_SIZE; ++row)
	{
		if (gameBoardValue(board, row, col) == value)
			return false;
	}
	return true;
}

bool gameBoardGroupAllowsValue(GameBoard board, int r, int c, int value)
{
	r = 3*(r/3); // get first row in group
	c = 3*(c/3); // get first column in group
	
	for	(int row = r; row < GROUP_SIZE; ++row)
	{
		for (int col = c; col < GROUP_SIZE; ++col) 
		{
			if (gameBoardValue(board, row, col) == value)
				return false;
		}
	}
	return true;
}

bool gameBoardAllowsValue(GameBoard board, int row, int column, int value)
{
	if (!gameBoardRowAllowsValue(board, row, value))
		return false;
	if (!gameBoardColumnAllowsValue(board, column, value))
		return false;
	if (!gameBoardGroupAllowsValue(board, row, column, value))
		return false;
	
	return true;
}

bool gameBoardIsComplete(GameBoard board)
{
	for	(int row = 0; row < LINE_SIZE; ++row)
	{
		for (int col = 0; col < LINE_SIZE; ++col) 
		{
			if (!indexIsValid(gameBoardValue(board, row, col)))
				return false;
		}
	}
	return true;
}

void gameBoardFirstOpenSpace(GameBoard board, int* r, int* c)
{
	for	(int row = 0; row < LINE_SIZE; ++row)
	{
		for (int col = 0; col < LINE_SIZE; ++col)
		{
			if (!indexIsValid(gameBoardValue(board, row, col)))
			{
				*r = row;
				*c = col;
				return;
			}
		}
	}
	*r = -1;
	*c = -1;
}
