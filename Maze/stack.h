#ifndef _STACK_H
#define _STACK_H

typedef char ElementType;

struct Cell;
typedef struct Cell *PtrToCell;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(PtrToCell X, Stack S);
PtrToCell Top(Stack S);
PtrToCell Pop(Stack S);

struct Cell
{
	ElementType Element;
	PtrToCell Parent;
	int x;
	int y;
};

struct Node
{
	PtrToCell CellElement;
	PtrToNode Next;
};

#endif
