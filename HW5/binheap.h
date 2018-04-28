#ifndef _BinHeap_H
#define _BinHeap_H

typedef int Priority;

struct QueueCell;
typedef struct QueueCell *PtrToQueueCell;
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeQueueEmpty(PriorityQueue H);
void InsertQueue(PtrToQueueCell X, PriorityQueue H);
PtrToQueueCell GetMin(PriorityQueue H);
PtrToQueueCell FindMin(PriorityQueue H);
PtrToQueueCell CreateQueueCell(Priority F, int member, PtrToQueueCell Parent);
int QueueIsEmpty(PriorityQueue H);
int QueueIsFull(PriorityQueue H);

struct QueueCell
{
	Priority F;
	int member;
	PtrToQueueCell Parent;
};

struct HeapStruct
{
	int Capacity;
	int Size;
	PtrToQueueCell *QueueCells;
};

#endif
