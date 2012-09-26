//
//  UserInteraction.h
//  PointerPlayground
//
//  Created by Yating Sheng on 12/15/11.
//  Copyright 2011 University of Michigan . All rights reserved.
//

#ifndef PointerPlayground_UserInteraction_h
#define PointerPlayground_UserInteraction_h

#include <stdbool.h>

typedef enum
{
	DialogMessageSetOrDelete,
	DialogMessageWhichLocation,
	DialogMessageReplaceANumberOrNot,
	DialogMessageNotRealLocation,
	DialogMessageWhatNumber,
	DialogMessagePermanentPosition,
	DialogMessageNoNumber,
	DialogMessageCannotPutThere,
	DialogMessageWon
} DialogMessage;

char gameGetInput(char* characters);
bool gameGetYesOrNo();

void gameAskUserForLocation(int* row, int* col);
int gameUserInputNumber();

void printDialog(DialogMessage message);

#endif
