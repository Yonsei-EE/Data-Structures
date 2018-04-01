#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "binheap.h"

#define mazeWidth 15 
#define mazeHeight 15 
 
void delay(int milli_seconds)
{
	// Converting time into milli_seconds
	// int milli_seconds = 1000 * number_of_seconds;

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

	printf("\n*: obstacles\n?: investigations"
			"\nX: visited\n#: shortest path\n");
	
	putchar('\n');
	for(i=0; i<mazeHeight; i++) {
		for(j=0; j<mazeWidth; j++) {
			printf("%c ", maze[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}

// Calculate cost = actual cost + manhatten distance
int calF(int x, int y, int G) {
	return G + sqrt(pow((mazeWidth-1-x),2) + pow((mazeHeight-1-y),2));
}

// Calculate actual cost
int calG(int x, int y, int F) {
	return F - sqrt(pow((mazeWidth-1-x),2) + pow((mazeHeight-1-y),2));
}

// Create node containing necessary information
PtrToCell createNode(Priority G, PtrToCell Parent, int x, int y) {
	PtrToCell newNode = malloc(sizeof(struct Cell));
	newNode->G = G;
	newNode->F = calF(x, y, G);
	newNode->Parent = Parent;
	newNode->x = x;
	newNode->y = y;
}

// Explore node in fringe with most significant priority (shortest distance)
PtrToCell exploreNode(char maze[mazeWidth][mazeHeight], PriorityQueue fringe) {
	int i, x, y;
	PtrToCell currentNode, newNode;

	// Dequeue the fringe. If empty, return NULL (failure)
	if(!IsEmpty(fringe))
		currentNode = GetMin(fringe);
	else
		return NULL;

	// Get position for current node. Check current node as visited
	x = currentNode->x;
	y = currentNode->y;
	maze[x][y] = 'X';

	// If reaches goal, return the goal node
	if(x==mazeWidth-1 && y==mazeHeight-1)
		return currentNode;

	// Find non-wall, non-visited, non-fringed adjacent nodes (counter-clockwise direction)
	if(x!=mazeWidth-1 && maze[x+1][y]!='*' && maze[x+1][y]!='X'
		       	&& maze[x+1][y]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x+1, y);
		Insert(newNode, fringe);
		maze[x+1][y] = '?';
	}
	if(x!=mazeWidth-1 && y!=0 && maze[x+1][y-1]!='*' && maze[x+1][y-1]!='X'
		       	&& maze[x+1][y]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x+1, y-1);
		Insert(newNode, fringe);
		maze[x+1][y-1] = '?';
	}
	if(y!=0 && maze[x][y-1]!='*' && maze[x][y-1]!='X'
		       	&& maze[x][y-1]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x, y-1);
		Insert(newNode, fringe);
		maze[x][y-1] = '?';
	}
	if(x!=0 && y!=0 && maze[x-1][y-1]!='*' && maze[x-1][y-1]!='X'
		       	&& maze[x-1][y-1]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x-1, y-1);
		Insert(newNode, fringe);
		maze[x-1][y-1] = '?';
	}
	if(x!=0 && maze[x-1][y]!='*' && maze[x-1][y]!='X'
		       	&& maze[x-1][y]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x-1, y);
		Insert(newNode, fringe);
		maze[x-1][y] = '?';
	}
	if(x!=0 && y!=mazeHeight-1 && maze[x-1][y+1]!='*' && maze[x-1][y+1]!='X'
		       	&& maze[x-1][y+1]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x-1, y+1);
		Insert(newNode, fringe);
		maze[x-1][y+1] = '?';
	}
	if(y!=mazeHeight-1 && maze[x][y+1]!='*' && maze[x][y+1]!='X'
		       	&& maze[x][y+1]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x, y+1);
		Insert(newNode, fringe);
		maze[x][y+1] = '?';
	}
	if(x!=mazeWidth-1 && y!=mazeHeight-1
		       	&& maze[x+1][y+1]!='*'&& maze[x+1][y+1]!='X'
		       	&& maze[x+1][y+1]!='?') {
		newNode = createNode(currentNode->G+1,
				currentNode, x+1, y+1);
		Insert(newNode, fringe);
		maze[x+1][y+1] = '?';
	}
	
	// Comment out to disable animation
	printf("Finding path for maze...\n");
	printMaze(maze);
	printf("\n\n");
	delay(500);

	// Recursively explore next node
	return exploreNode(maze, fringe);
}

// Find shortest path by backtracking ancestor nodes of goal node
void setShortestPath(char maze[mazeWidth][mazeHeight], PtrToCell goal) {
	PtrToCell parent = goal;

	while(parent!=NULL) {
		maze[parent->x][parent->y] = '#';
		parent = parent->Parent;

		// Comment out to disable animation
		printf("Finding path for maze...\n");
		printMaze(maze);
		printf("\n\n");
		delay(200);
	}
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
	int i, j;
	char maze[mazeWidth][mazeHeight];
	PtrToCell temp, startNode;
	PriorityQueue fringe = Initialize(1000);
	
	setMaze(maze);

	printf("Generating maze...\n");
	printMaze(maze);

	startNode = createNode(0,NULL,0,0);
	Insert(startNode, fringe);
	temp = exploreNode(maze, fringe);

	// Print success or failure
	if(temp!=NULL) {
		setShortestPath(maze, temp);
		printf("Success!\n");
	}
	else
		printf("Failure..\n");

	// Print final maze
	printMaze(maze);
	
	// Print performance data
	if(temp!=NULL)
		printf("Shortest path length: %d\n", temp->G);
	else
		putchar('\n');
	printf("Total number of visited nodes: %d\n", calX(maze));

	Destroy(fringe);

	return 0;
}
