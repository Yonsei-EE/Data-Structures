#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

#define mazeWidth 15
#define mazeHeight 15

PtrToCell createNode(Priority F, PtrToCell Parent, int x, int y) {
	PtrToCell newNode = malloc(sizeof(struct Cell));
	newNode->F = F;
	newNode->Parent = Parent;
	newNode->x = x;
	newNode->y = y;
}

PtrToCell exploreNode(char maze[mazeWidth][mazeHeight], PriorityQueue fringe) {
	int i, x, y;
	PtrToCell currentNode, newNode;

	currentNode = getMin(fringe);
	x = currentNode->x;
	y = currentNode->y;

	// find non-wall adjacent nodes
	if(x!=mazeWidth && maze[x+1][y]!='*')
		


	for(i=0; i<2; i++) {
		newNode = createNode(3-i,NULL,0,i);
		Insert(newNode, fringe);
	}


}

void SetMaze(char maze[mazeWidth][mazeHeight]) {
	int i, j;
	long seed;

	// Initialize maze
	for(i=0; i<mazeHeight; i++) {
		for(j=0; j<mazeWidth; j++) {
			maze[j][i] = '0';
		}
	}

	// Get random seed
	printf("Type your student number: ");
	scanf("%ld", &seed);
	srand(seed);
	for(i=0; i<mazeWidth*mazeHeight/2; i++) {
		maze[rand()%mazeWidth][rand()%mazeHeight] = '*';
	}

	// Set the start and goal
	maze[0][0] = '0';
	maze[mazeWidth-1][mazeHeight-1] = '0';

	// Print maze
	for(i=0; i<mazeHeight; i++) {
		for(j=0; j<mazeWidth; j++) {
			printf("%c ", maze[j][i]);
		}
		printf("\n");
	}
}

int main()
{
	int i, j;
	char maze[mazeWidth][mazeHeight];
	PtrToCell temp, startNode;
	PriorityQueue fringe = Initialize(1000);
	
	SetMaze(maze);

	exploreNode(maze, fringe);

	temp = GetMin(fringe);
	printf("(%d,%d)\n", temp->x, temp->y);

	return 0;
}
