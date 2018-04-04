#ifndef _List_H
#define _List_H

typedef int ElementType;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List ListMakeEmpty(List L);
int ListIsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType x, ElementType y, List L);
void Delete(ElementType x, ElementType y, List L);
Position FindPrevious(ElementType x, ElementType, List L);
void ListInsert(ElementType x, ElementType y, List L, Position P);
void DeleteList(List L);
void PrintList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);

struct Node
{
	ElementType x;
	ElementType y;
	Position    Next;
};

#endif
#pragma once
