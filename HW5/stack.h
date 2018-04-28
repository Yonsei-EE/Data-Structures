#ifndef _STACK_H
#define _STACK_H

struct Cell;
typedef struct Cell *PtrToCell;
struct StackNode;
typedef struct StackNode *PtrToStackNode;
typedef PtrToStackNode Stack;

int StackIsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeStackEmpty(Stack S);
void Push(PtrToCell X, Stack S);
PtrToCell CreateCell(int member, PtrToCell parent);
PtrToCell Top(Stack S);
PtrToCell PopStack(Stack S);

struct Cell
{
	int member;
	PtrToCell parent;
};

struct StackNode
{
	PtrToCell CellElement;
	PtrToStackNode Next;
};

#endif
