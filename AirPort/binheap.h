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
int Findi(int ID, PriorityQueue H);
PtrToCell Find(int ID, PriorityQueue H);
PtrToCell GetMin(PriorityQueue H);
PtrToCell FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
void PrintQueue(PriorityQueue H);
void Delete(int i, PriorityQueue H);

struct Cell
{
	Priority F;
	int Fuel;
	int ID;
};

struct HeapStruct
{
	int Capacity;
	int Size;
	PtrToCell *Cells;
};

#endif
