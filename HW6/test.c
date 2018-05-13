#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

int main() {
	PtrToCell temp, cell;
	PriorityQueue H = Initialize(100);
	cell = malloc(sizeof(struct Cell));
	cell->x = 0;
	cell->y = 0;
	cell->F = 1.0;
	Insert(cell, H);
	temp = Find(0,0,H);
	cell = malloc(sizeof(struct Cell));
	cell->x = 0;
	cell->y = 0;
	cell->F = 0.0;
	Insert(cell, H);

	temp = Find(0,0,H);
	printf("%d %d %lf %d\n", temp->x, temp->y, temp->F, H->Size);
}	
