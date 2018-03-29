#include <stdio.h>
#include "binheap.h"
#include <stdlib.h>

PtrToCell NewNode(Priority F, PtrToCell Parent, int x, int y) {
	PtrToCell newNode = malloc(sizeof(struct Cell));
	newNode->F = F;
	newNode->Parent = Parent;
	newNode->x = x;
	newNode->y = y;
}

int main()
{
	int i, j;
	long seed;
	char maze[15][15];
	PtrToCell Temp, newNode;
	
	// Initialize maze
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++) {
			maze[j][i] = '0';
		}
	}

	// Get random seed
	printf("Type your student number: ");
	scanf("%ld", &seed);
	srand(seed);
	for(i=0; i<15*15/2; i++) {
		maze[rand()%15][rand()%15] = '*';
	}

	// Set the start and goal
	maze[0][0] = '0';
	maze[14][14] = '0';

	// Print maze
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++) {
			printf("%c ", maze[j][i]);
		}
		printf("\n");
	}

	PriorityQueue Q = Initialize(1000);

	for(i=0; i<2; i++) {
		newNode = NewNode(3-i,NULL,0,i);
		Insert(newNode, Q);
	}

	Temp = GetMin(Q);
	printf("(%d,%d)\n", Temp->x, Temp->y);

	return 0;
}
