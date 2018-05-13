#ifndef _BinHeap_H
#define _BinHeap_H

typedef int Priority;

struct Cell;
typedef struct Cell *PtrToCell;
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(PtrToCell X, PriorityQueue H);
int Findi(int x, int y, PriorityQueue H);
PtrToCell Find(int x, int y, PriorityQueue H);
PtrToCell GetMin(PriorityQueue H);
PtrToCell FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

struct Cell
{
	Priority G;
	double F;
	PtrToCell Parent;
	int x;
	int y;
};

struct HeapStruct
{
	int Capacity;
	int Size;
	PtrToCell *Cells;
};

#endif
