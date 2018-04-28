#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List MakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = (List)malloc(sizeof(struct Node));
	if (L == NULL)
		printf("Out of memory!");
	L->Next = NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

int IsLast(Position P, List L)
{
	return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
	Position P;

	P = L->Next;
	while (P != NULL && P->Element != X)
		P = P->Next;

	return P;
}

void Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

ElementType Pop(List L)
{
	ElementType X;
	Position TmpCell;

	if(!IsEmpty(L)) {
		TmpCell = L->Next;
		L->Next = TmpCell->Next;
		X = TmpCell->Element;
		free(TmpCell);
	}
	
	return X;
}	

Position FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;

	return P;
}

void Insert(ElementType X, ElementType Y, List L, Position P)
{
	Position TmpCell;

	TmpCell = (List)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element = X;
	TmpCell->Intimacy = Y;
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
		printf("%d ", P->Element);
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

ElementType RetrieveElement(Position P)
{
	return P->Element;
}

ElementType RetrieveIntimacy(Position P)
{
	return P->Intimacy;
}
