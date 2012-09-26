//
//  GameBoard.h
//  PointerPlayground
//
//  Created by Yating Sheng on 12/13/11.
//  Copyright 2011 University of Michigan . All rights reserved.
//

#ifndef PointerPlayground_GameBoard_h
#define PointerPlayground_GameBoard_h

#include <stdbool.h>

#define GROUP_SIZE          (3)
#define LINE_SIZE           (GROUP_SIZE*GROUP_SIZE)
#define BOARD_SIZE			(LINE_SIZE*LINE_SIZE)
#define BLANK_ELEMENT       (-1)
#define UNDERLINE_ELEMENT   (-2)

/*
struct _GameBoardSpace {
	int value;
	bool permanent;
};
typedef struct _GameBoardSpace GameBoardSpace;
*/

typedef struct _GameBoardSpace 
{
	int value;
	bool permanent;
} GameBoardSpace;

typedef GameBoardSpace GameBoard[BOARD_SIZE];

bool indexIsValid(int index);
bool valueIsValid(int value);

bool gameBoardInitializeFromFile(GameBoard board, char* filename);

void gameBoardSetValue(GameBoard board, int row, int column, int value);
int gameBoardValue(GameBoard board, int row, int column);

void gameBoardValueSetPermanent(GameBoard board, int row, int column, bool permanent);
bool gameBoardValuePermanent(GameBoard board, int row, int column);

void gameBoardPrint(GameBoard board);

bool gameBoardAllowsValue(GameBoard board, int row, int column, int value);

bool gameBoardIsComplete(GameBoard board);

void gameBoardFirstOpenSpace(GameBoard board, int* row, int* col);

#endif
