#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

#define MinPQSize (5)
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
		H->Cells = malloc((MaxElements + 1) * sizeof(PtrToCell));
		if(H->Cells == NULL)
			printf("Element out of space!!!");
		else {
			H->Capacity = MaxElements;
			H->Size = 0;
			H->Cells[0] = malloc(sizeof(struct Cell));
			H->Cells[0]->F = MinData;
		}
	}

	return H;
}

void MakeEmpty(PriorityQueue H)
{
	H->Size = 0;
}

void Insert(PtrToCell X, PriorityQueue H)
{
	int i, Child;
	PtrToCell LastElement;

	if(IsFull(H))
	{
		printf("Priority queue is full");
		return;
	}

	i = Findi(X->ID, H);
	if(i!=-1 && H->Cells[i]->F > X->F) {
		LastElement = H->Cells[H->Size--];

		for(;i*2 <= H->Size; i=Child)
		{
			Child = i * 2;
			if(Child != H->Size && H->Cells[Child+1]->F < H->Cells[Child]->F)
				Child++;
			if(LastElement->F > H->Cells[Child]->F)
				H->Cells[i] = H->Cells[Child];
			else
				break;
		}

		H->Cells[i] = LastElement;
	}

	if(i==-1 || H->Cells[i]->F > X->F) {
		for(i = ++H->Size; H->Cells[i/2]->F>X->F; i/=2)
			H->Cells[i] = H->Cells[i/2];
		H->Cells[i] = X;
	}
}

int Findi(int ID, PriorityQueue H)
{
	PtrToCell temp = NULL;
	int i, n=-1;

	for(i=1; i<H->Size+1; i++) {
		if(H->Cells[i]->ID==ID) {
			n = i;
			break;
		}
	}

	return n;
}

PtrToCell Find(int ID, PriorityQueue H)
{
	PtrToCell temp = NULL;
	int i;

	for(i=1; i<H->Size+1; i++) {
		if(H->Cells[i]->ID==ID)
			temp = H->Cells[i];
	}

	return temp;
}

PtrToCell GetMin(PriorityQueue H)
{
	int i, Child;
	PtrToCell MinElement, LastElement;

	if(IsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->Cells[0];
	}

	MinElement = H->Cells[1];
	LastElement = H->Cells[H->Size--];

	for(i=1; i*2 <= H->Size; i=Child)
	{
		Child = i * 2;
		if(Child != H->Size && H->Cells[Child+1]->F < H->Cells[Child]->F)
			Child++;
		if(LastElement->F > H->Cells[Child]->F)
			H->Cells[i] = H->Cells[Child];
		else
			break;
	}

	H->Cells[i] = LastElement;

	return MinElement;
}

PtrToCell FindMin(PriorityQueue H)
{
	if(!IsEmpty(H))
		return H->Cells[1];
	printf("Priority Queue is Empty");
	return H->Cells[0];
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

void Destroy(PriorityQueue H)
{
	int i;
	for(i=0; i<H->Size; i++) {
		free(H->Cells[i]);
	}
	free(H->Cells);
	free(H);
}

void PrintQueue(PriorityQueue H)
{
	for(int i=1; i<H->Size+1; i++) {
		if(i==H->Size) {
			printf("ID:%d Fuel:%d\n",H->Cells[i]->ID,H->Cells[i]->Fuel);
			break;
		}
		printf("ID:%d Fuel:%d,\t",H->Cells[i]->ID,H->Cells[i]->Fuel);
	}
	if(IsEmpty(H))
		putchar('\n');
}

void Delete(int i, PriorityQueue H) {
	PtrToCell LastElement;
	int Child;
	LastElement = H->Cells[H->Size--];

	for(;i*2 <= H->Size; i=Child)
	{
		Child = i * 2;
		if(Child != H->Size && H->Cells[Child+1]->F < H->Cells[Child]->F)
			Child++;
		if(LastElement->F > H->Cells[Child]->F)
			H->Cells[i] = H->Cells[Child];
		else
			break;
	}

	H->Cells[i] = LastElement;
}

#if 0
#endif
