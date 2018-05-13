#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stack.h"

#define mazeWidth 15 
#define mazeHeight 15 
 
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds);
}

// Setup maze randomly
void setMaze(char maze[mazeWidth][mazeHeight]) {
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

	// Generate obstacles that covers 50% of the maze
	for(i=0; i<mazeWidth*mazeHeight/2; i++) {
		maze[rand()%mazeWidth][rand()%mazeHeight] = '*';
	}

	// Set the start and goal
	maze[0][0] = '0';
	maze[mazeWidth-1][mazeHeight-1] = '0';
}

void printMaze(char maze[mazeWidth][mazeHeight]) {
	int i, j;

	printf("\n*: obstacles\nX: visited\n#: shortest path\n");
	
	putchar('\n');
	for(i=0; i<mazeHeight; i++) {
		for(j=0; j<mazeWidth; j++) {
			printf("%c ", maze[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}

// Create node containing simply coordinates
PtrToCell createNode(int x, int y) {
	PtrToCell newNode = malloc(sizeof(struct Cell));
	newNode->x = x;
	newNode->y = y;

	return newNode;
}

// Explore node in fringe with depth first search
int exploreNode(char maze[mazeWidth][mazeHeight], Stack fringe) {
	int i, x, y, success=0;
	PtrToCell currentNode, newNode;

	// Get position for current node. Check current node as visited
	currentNode = Top(fringe);
	x = currentNode->x;
	y = currentNode->y;
	maze[x][y] = 'X';
	
	// Comment out to disable animation
	printf("Finding path for maze...\n");
	printMaze(maze);
	printf("\n\n");
	delay(100);

	// If reaches goal, return success
	if(x==mazeWidth-1 && y==mazeHeight-1)
		return 1;

	// Find and explore non-wall, non-visited, adjacent nodes (clockwise direction)
	if(x!=mazeWidth-1 && maze[x+1][y]!='*' && maze[x+1][y]!='X' && !success) {
		newNode = createNode(x+1, y);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(x!=mazeWidth-1 && y!=mazeHeight-1
		       	&& maze[x+1][y+1]!='*'&& maze[x+1][y+1]!='X' && !success) {
		newNode = createNode(x+1, y+1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(y!=mazeHeight-1 && maze[x][y+1]!='*' && maze[x][y+1]!='X' && !success) {
		newNode = createNode(x, y+1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(x!=0 && y!=mazeHeight-1 && maze[x-1][y+1]!='*' && maze[x-1][y+1]!='X' && !success) {
		newNode = createNode(x-1, y+1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(x!=0 && maze[x-1][y]!='*' && maze[x-1][y]!='X' && !success) {
		newNode = createNode(x-1, y);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(x!=0 && y!=0 && maze[x-1][y-1]!='*' && maze[x-1][y-1]!='X' && !success) {
		newNode = createNode(x-1, y-1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(y!=0 && maze[x][y-1]!='*' && maze[x][y-1]!='X' && !success) {
		newNode = createNode(x, y-1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}
	if(x!=mazeWidth-1 && y!=0 && maze[x+1][y-1]!='*' && maze[x+1][y-1]!='X' && !success) {
		newNode = createNode(x+1, y-1);
		Push(newNode, fringe);
		success = exploreNode(maze, fringe);
	}

	// If unsuccessful, pop the dead node
	if(!success)
		Pop(fringe);

	// Return the outcome
	return success;
}

// Find path. For DFS, the fringe itself is the path. 
int setPath(char maze[mazeWidth][mazeHeight], Stack fringe) {
	PtrToCell cell = NULL;
	int length = 0;

	while(!IsEmpty(fringe)) {
		cell = Pop(fringe);
		maze[cell->x][cell->y] = '#';
		length++;

		// Comment out to disable animation
		printf("Finding path for maze...\n");
		printMaze(maze);
		printf("\n\n");
		delay(100);
	}

	return length;
}

// Calculate how many nodes were visited
int calX(char maze[mazeWidth][mazeHeight]) {
	int i, j, numOfX = 0;
	for(i=0; i<mazeHeight; i++) {
		for(j=0; j<mazeWidth; j++) {
			if(maze[j][i]=='X' || maze[j][i]=='#')
				numOfX++;
		}
	}

	return numOfX;
}

int main()
{
	int i, j, success=0, pathlength;
	char maze[mazeWidth][mazeHeight];
	PtrToCell startNode;
	Stack fringe = CreateStack();
	
	setMaze(maze);

	printf("Generating maze...\n");
	printMaze(maze);

	startNode = createNode(0,0);
	Push(startNode, fringe);
	success = exploreNode(maze, fringe);

	// Print success or failure
	if(success) {
		pathlength = setPath(maze, fringe);
		printf("Success!\n");
	}
	else
		printf("Failure..\n");

	// Print final maze
	printMaze(maze);
	
	// Print performance data
	if(success)
		printf("Path length: %d\n", pathlength);
	else
		putchar('\n');
	printf("Total number of visited nodes: %d\n", calX(maze));

	MakeEmpty(fringe);
	DisposeStack(fringe);

	return 0;
}
