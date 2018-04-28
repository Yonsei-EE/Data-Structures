#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int StackIsEmpty(Stack S)
{
	return S->Next == NULL;
}

Stack CreateStack()
{
	Stack S;

	S = malloc(sizeof(struct StackNode));

	if(S == NULL)
		printf("Out of space!");

	return S;
}

void DisposeStack(Stack S)
{
	if(S != NULL)
		free(S);
}

void MakeStackEmpty(Stack S)
{
	if(S == NULL)
		printf("Must use CreateStack first");
	else
	{
		while(!StackIsEmpty(S))
			PopStack(S);
	}
}

void Push(PtrToCell CurrentCell, Stack S)
{
	PtrToStackNode TmpCell;

	TmpCell = malloc(sizeof(struct StackNode));
	if(TmpCell == NULL)
		printf("Out of space!");
	else
	{
		TmpCell->CellElement = CurrentCell;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}

PtrToCell CreateCell(int member, PtrToCell parent)
{
	PtrToCell newCell= malloc(sizeof(struct Cell));
	newCell->member = member;
	newCell->parent = parent;
}
	

PtrToCell Top(Stack S)
{
	if(!StackIsEmpty(S))
		return S->Next->CellElement;
	else
		printf("Empty Stack");

	return 0;
}

PtrToCell PopStack(Stack S)
{
	PtrToStackNode FirstNode;
	PtrToCell FirstCell;

	if(StackIsEmpty(S))
		return NULL;
	else
	{
		FirstNode = S->Next;
		FirstCell = FirstNode->CellElement;
		S->Next = S->Next->Next;
		free(FirstNode);
	}

	return FirstCell;
}
