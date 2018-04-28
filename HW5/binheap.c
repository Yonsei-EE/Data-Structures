#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

#define MinPQSize (10)
#define MinData (-32767)

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	if(MaxElements < MinPQSize) {
		printf("Priority queue size is too small");
		return NULL;
	}

	H = malloc(sizeof(struct HeapStruct));

	if(H == NULL)
		printf("Heap out of space!!!");
	else {
		H->QueueCells = malloc((MaxElements + 1) * sizeof(PtrToQueueCell));
		if(H->QueueCells == NULL)
			printf("Element out of space!!!");
		else {
			H->Capacity = MaxElements;
			H->Size = 0;
			H->QueueCells[0] = malloc(sizeof(struct QueueCell));
			H->QueueCells[0]->F = MinData;
		}
	}

	return H;
}

void MakeQueueEmpty(PriorityQueue H)
{
	H->Size = 0;
}

void InsertQueue(PtrToQueueCell X, PriorityQueue H)
{
	int i;

	if(QueueIsFull(H))
	{
		printf("Priority queue is full");
		return;
	}

	for(i = ++H->Size; H->QueueCells[i/2]->F>X->F; i/=2)
		H->QueueCells[i] = H->QueueCells[i/2];
	H->QueueCells[i] = X;
}

PtrToQueueCell GetMin(PriorityQueue H)
{
	int i, Child;
	PtrToQueueCell MinElement, LastElement;

	if(QueueIsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->QueueCells[0];
	}

	MinElement = H->QueueCells[1];
	LastElement = H->QueueCells[H->Size--];

	for(i=1; i*2 <= H->Size; i=Child)
	{
		Child = i * 2;
		if(Child != H->Size && H->QueueCells[Child+1]->F < H->QueueCells[Child]->F)
			Child++;
		if(LastElement->F > H->QueueCells[Child]->F)
			H->QueueCells[i] = H->QueueCells[Child];
		else
			break;
	}

	H->QueueCells[i] = LastElement;

	return MinElement;
}

PtrToQueueCell FindMin(PriorityQueue H)
{
	if(!QueueIsEmpty(H))
		return H->QueueCells[1];
	printf("Priority Queue is Empty");
	return H->QueueCells[0];
}

PtrToQueueCell CreateQueueCell(Priority F, int member, PtrToQueueCell Parent) {
	PtrToQueueCell cell = malloc(sizeof(struct QueueCell));
	cell->F = F;
	cell->member = member;
	cell->Parent = Parent;

	return cell;
}

int QueueIsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int QueueIsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

void Destroy(PriorityQueue H)
{
	int i;
	for(i=0; i<H->Size; i++) {
		free(H->QueueCells[i]);
	}
	free(H->QueueCells);
	free(H);
}

#if 0
#endif
