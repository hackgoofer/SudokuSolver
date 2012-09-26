//  main.c
//  PointerPlayground
//
//  Created by Yating Sheng on 12/9/11.
//  Copyright 2011 University of Michigan . All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

#include "GameBoard.h"
#include "UserInteraction.h"

void userSetGameBoardValue(GameBoard board)
{
	int row, col, value;
	bool permanent;
	
	printDialog(DialogMessageWhichLocation);
	gameAskUserForLocation(&row, &col);
	value = gameBoardValue(board, row, col);
	permanent = gameBoardValuePermanent(board, row, col);
	
	if (!permanent)
	{
		if (indexIsValid(value)) // if there is a number there
		{
			printDialog(DialogMessageReplaceANumberOrNot);
			if (!gameGetYesOrNo())
				return;
		}		
		gameBoardSetValue(board, row, col, UNDERLINE_ELEMENT);
		gameBoardPrint(board);
		printDialog(DialogMessageWhatNumber);
		value = gameUserInputNumber();
		
		// check if it is OK to put the value there
		if (!gameBoardAllowsValue(board, row, col, value))
		{
			printDialog(DialogMessageCannotPutThere);
			gameBoardSetValue(board, row, col, BLANK_ELEMENT);
			gameBoardPrint(board);
		}
		else
		{
			gameBoardSetValue(board, row, col, value);
			gameBoardPrint(board);
		}
	}
	else
		printDialog(DialogMessagePermanentPosition);
}

void userDeleteGameBoardValue(GameBoard board)
{
	int row, col, value;
	bool permanent;
	
	printDialog(DialogMessageWhichLocation);
	gameAskUserForLocation(&row, &col);
	value = gameBoardValue(board, row, col);
	permanent = gameBoardValuePermanent(board, row, col);
	
	if (!permanent)
	{
		if (indexIsValid(value)) // if there is a number there
		{
			gameBoardSetValue(board, row, col, BLANK_ELEMENT);
			gameBoardPrint(board);
		}
		else
			printDialog(DialogMessageNoNumber);
	}
	else
		printDialog(DialogMessagePermanentPosition);
}

bool solveBoard(GameBoard board)
{
//	gameBoardPrint(board);
	
	int row;
	int col;
	gameBoardFirstOpenSpace(board, &row, &col);
	if (-1 == row && -1 == col)
		return true;
	
	for (int i = 0; i < LINE_SIZE; ++i)
	{
		if (gameBoardAllowsValue(board, row, col, i))
		{
//			printf("Trying %d at %c%d.\n", i+1, row+'A', col+1);
			
			gameBoardSetValue(board, row, col, i);
			if (solveBoard(board))
				return true;
			gameBoardSetValue(board, row, col, BLANK_ELEMENT);
		}
	}
	
	return false;
}

void solve(GameBoard board)
{
	if(!solveBoard(board))
		printf("Failed to solve the board.\n");
	else
		printDialog(DialogMessageWon);
	
	gameBoardPrint(board);
}

void play(GameBoard board)
{
	while (!gameBoardIsComplete(board))
    {
        printDialog(DialogMessageSetOrDelete);
		char decision = gameGetInput("sd");
		
		switch (decision)
		{
			case 's':
				userSetGameBoardValue(board);
				break;
			default: // 'd'
				userDeleteGameBoardValue(board);
				break;
		}
	}
}

int main()
{	
    GameBoard board;
    gameBoardInitializeFromFile(board, "/Users/dreamfly1208/Desktop/Programming/PointerPlayground/PointerPlayground/puzzle.txt");
    gameBoardPrint(board);
	
	printf("Would you like to solve it (s) or play it (p)?\n");
	char decision = gameGetInput("sp");
	
	switch (decision) 
	{
		case 's':
			solve(board);
			break;
		default: // 'p'
			play(board);
			break;
	}
	
    return 0;
}


/*
 int main()
 {
 // 4 bytes, 0-(256^1-1), 256^1-(256^2-1), 256^2-(256^3-1)...
 // mem:  15       14       13       12
 // 00000100 00000011 00000010 00000001
 //                      512       1
 
 // 0, 1, 10, 11, 100, 101, 110, 111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111
 // 0, 1,  2,  3,   4,   5,   6,   7,    8,    9,    A,    B,    C,    D,    E,    F <- hexadecimal 
 
 char memory[100]; // 00000000, 00000001, 00000010, 3, 4, 5, ...
 
 for (int i = 0; i < 100; ++i)
 memory[i] = i;
 
 short* p = memory;
 
 
 // 123 = 3*10^0 + 2*10^1 + 1*10^2
 
 // 00000001 00000010
 
 // 1*256^0 + 2*256^1 = 513
 // 
 printf("%d\n", p[2]); // 0 + 1*256^1 + 2*256^2 + 3*256*256*256
 
 
 int a = 1 + 2*256 + 3*256*256 + 4*256*256*256;
 char* pa = &a;
 
 printf("If we treat 0x%X as %d bytes it is %d.\n", (char)pa, sizeof(char), *pa);
 */    









































 /*
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 
 typedef struct sNode
 {
 int data;
 struct sNode* next;
 }Node;
 
 struct sList
 {
 Node* front;
 };
 
 
 typedef struct sList* List;
 //Whats the difference between typedef struct and just 
 // L --> |a| --> |n| --> |n| --> |n| --> |n| --> x
 
 bool listIsEmpty(List l)
 {
 return l->front == NULL;
 }
 
 void listPrint(List l)
 {
 if (listIsEmpty(l))
 return;
 
 Node* n = l->front;
 while (NULL != n)
 {
 printf("%d ", n->data);
 n = n->next;
 }
 printf("\n");
 }
 
 void listPush(List l, int value) // add front
 {
 Node* n = (Node*)malloc(sizeof(Node));
 n->data = value;
 
 n->next = l->front;
 l->front = n;
 }
 
 void listPop(List l) // remove front
 {
 if (listIsEmpty(l))
 return;
 
 Node* n = l->front;
 l->front = l->front->next;
 free(n);
 }
 
 int listFirst(List l)
 {
 if (listIsEmpty(l))
 return -1;
 
 return l->front->data;
 }
 
 List listCreate()
 {
 List l = (List)malloc(sizeof(struct sList));
 //I dont understand this line!! Look at the one above as reference.
 l->front = NULL;
 return l;
 }
 
 void listClear(List l)
 {
 while (!listIsEmpty(l))
 listPop(l);
 }
 
 void listDestroy(List l)
 {
 listClear(l);
 
 free(l);
 }
 
 void listRemoveLast(List l)
 {
 // remove the LAST element of the list
 }
 
 void listAddEnd(List l, int value)
 {
 // add the value to the END of the list
 }
 
 // L
 // |------> node (data)
 //            |----------> x
 
 int main()
 {
 List l = listCreate();
 
 listPush(l, 10);
 listPush(l, 8);
 listPush(l, 6);
 listPush(l, 4);
 listPush(l, 2);
 
 listPop(l);
 
 listPrint(l);
 printf("%d\n", listFirst(l));
 
 listDestroy(l);
 
 return 0;
 }


*/

















/*
 int* giveMeAPointer()
 {
 return malloc(4);
 }
 
 void eatMyPointer(int *p)
 {
 free(p);
 }
 
 int main()
 {
 int* p = giveMeAPointer();
 int* q = giveMeAPointer();
 
 *p = 4;
 *q = 5;
 
 printf("%d and %d in the %d and %d\n", *p, *q, (int)p, (int)q);
 
 eatMyPointer(p);
 eatMyPointer(q);
 
 return 0;
 }
 */


/*
 void printArray(int* array, int length)
 {
 for (int i = 0; i < length; ++i)
 {
 printf("%d", array[i]);
 
 if (i != length - 1)
 printf(" ");
 }
 
 printf("\n");
 }
 
 void changeValue(int* array, int location, int value)
 {
 array[location] = value;
 }
 
 int main()
 {
 int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
 printArray(a, sizeof(a)/sizeof(int));
 changeValue(a, 3, 13);
 changeValue(a, 5, 139);
 printArray(a, sizeof(a)/sizeof(int));
 
 return 0;
 }
 */


/*
 
 
 int main()
 {
 int p = 8;
 int q = (int)&p;
 int* r = &p;
 
 printf("%d --> %d and %d\n", &p, r+1, q+1);
 
 return 0;
 }
 
 */

/* recursion:
 
 int fibonacci(int n)
 {
 if (0 == n || 1 == n)
 return 1;
 return fibonacci(n-1) + fibonacci(n-2);
 }
 
 int fibonacciLoop(int n)
 {
 int a = 1;
 int b = 1;
 
 while (n)
 {
 int result = a+b;
 a = b;
 b = result;
 --n;
 }
 return b;
 }
 
 int factorial(int n)
 {
 if (0 == n)
 return 1;
 return factorial(n-1)*n;
 }
 
 int factorialLoop(int n)
 {
 int result = 1;
 while (n)
 {
 result *= n;
 --n;
 }
 return result;
 }
 */