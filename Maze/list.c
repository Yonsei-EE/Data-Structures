#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List ListMakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = (List)malloc(sizeof(struct Node));
	if (L == NULL)
		printf("Out of memory!");
	L->Next = NULL;
	return L;
}

int ListIsEmpty(List L)
{
	return L->Next == NULL;
}

int IsLast(Position P, List L)
{
	return P->Next == NULL;
}

Position Find(ElementType x, ElementType y,  List L)
{
	Position P;

	P = L->Next;
	while (P != NULL && (P->x != x || P->y != y))
		P = P->Next;

	return P;
}

void Delete(ElementType x, ElementType y, List L)
{
	Position P, TmpCell;

	P = FindPrevious(x, y, L);

	if (!IsLast(P, L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

Position FindPrevious(ElementType x, ElementType y, List L)
{
	Position P;

	P = L;
	while (P->Next != NULL && (P->Next->x != x || P->Next->y != y))
		P = P->Next;

	return P;
}

void ListInsert(ElementType x, ElementType y, List L, Position P)
{
	Position TmpCell;

	TmpCell = (List)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->x = x;
	TmpCell->y = y;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}

void DeleteList(List L)
{
	Position P, Tmp;

	P = L->Next;
	L->Next = NULL;
	while (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}

void PrintList(List L)
{
	Position P;
	P = L->Next;
	while (P != NULL)
	{
		printf("(%d, %d) ", P->x, P->y);
		P = P->Next;
	}
}

Position Header(List L)
{
	return L;
}

Position First(List L)
{
	return L->Next;
}

Position Advance(Position P)
{
	return P->Next;
}
