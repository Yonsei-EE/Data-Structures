#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxSteps 1000
#define arenaSize 31

struct ant;
typedef struct ant *ptrToAnt;

struct ant
{
	int x;
	int y;
	int remainingSteps;
	int numFood;
};
 
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds);
}

ptrToAnt hatchAnt() {
	ptrToAnt tempAnt = NULL;
	tempAnt = malloc(sizeof(struct ant));
	if(tempAnt == NULL)
		printf("No room for any ants!\n");
	else {
		tempAnt->x = arenaSize/2;
		tempAnt->y = arenaSize/2;
		tempAnt->remainingSteps = maxSteps;
		tempAnt->numFood = 0;
	}

	return tempAnt;
}

// Setup arena randomly
void setArena(char arena[arenaSize][arenaSize]) {
	int i, j, numFood;
	long seed;

	// Initialize arena
	for(i=0; i<arenaSize; i++) {
		for(j=0; j<arenaSize; j++) {
			arena[j][i] = '0';
		}
	}

	// Get random seed
	printf("Type your student number: ");
	scanf("%ld", &seed);
	srand(seed);

	numFood = arenaSize*arenaSize/10;
	// Generate seeds that cover 10% of the arena
	for(i=0; i<numFood; i++) {
		arena[rand()%arenaSize][rand()%arenaSize] = '*';
	}
}

void printArena(char arena[arenaSize][arenaSize]) {
	int i, j;

	printf("\n*: food\n$: ant\n");

	putchar('\n');
	for(i=0; i<arenaSize; i++) {
		for(j=0; j<arenaSize; j++) {
			printf("%c ", arena[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}

// Look in a certain direction. Increment food count for every '*'. Return total food count.
int look(int xDir, int yDir, char arena[arenaSize][arenaSize], ptrToAnt ant) {
	int x = ant->x, y = ant->y;
	int numFood = 0;

	while(x>=0 && x<arenaSize && y>=0 && y<arenaSize) {
		x = x + xDir;
		y = y + yDir;

		if(x<0 || x>=arenaSize || y<0 || y>=arenaSize)
			break;

		if(arena[x][y]=='*')
			numFood++;
	}

	return numFood;
}	

// Determine where to go and perform action recursively.
void action(char arena[arenaSize][arenaSize], ptrToAnt ant) {
	int N, E, W, S, NE, NW, SE, SW, max;
	int xAction = 0, yAction = -1;

	// If all time steps are up, kill the system.
	if(ant->remainingSteps<0)
		return;

	printf("Remaining Time Steps: %d\n", ant->remainingSteps);

	// Look in all 8 directions. Get food counts for each direction.
	N = look(0,-1, arena, ant);
	E = look(1,0, arena, ant);
	W = look(-1,0, arena, ant);
	S = look(0,1, arena, ant);
	NE = look(1,-1, arena, ant);
	NW = look(-1,-1, arena, ant);
	SE = look(1,1, arena, ant);
	SW = look(-1,1, arena, ant);

	printf("NW:%d\tN:%d\tNE:%d\t\nW:%d\t\tE:%d\nSW:%d\tS:%d\tSE:%d\n",
			NW,N,NE,W,E,SW,S,SE);

	// Determine direction with greatest food count.
	max = N;
	if(E>max) {
		xAction = 1;
		yAction = 0;
		max = E;
	}
	if(W>max) {
		xAction = -1;
		yAction = 0;
		max = W;
	}
	if(S>max) {
		xAction = 0;
		yAction = 1;
		max = S;
	}
	if(NE>max) {
		xAction = 1;
		yAction = -1;
		max = NE;
	}
	if(NW>max) {
		xAction = -1;
		yAction = -1;
		max = NW;
	}
	if(SE>max) {
		xAction = 1;
		yAction = 1;
		max = SE;
	}
	if(SW>max) {
		xAction = -1;
		yAction = 1;
		max = SW;
	}

	printf("max: %d\n", max);

	// If unable to locate food, perform random action.
	if(max==0) {
		xAction = -1 + (int)rand()%3;
		yAction = -1 + (int)rand()%3;
	}

	// Move ant in determined direction.
	arena[ant->x][ant->y] = '0';

	ant->x = ant->x + xAction;
	ant->y = ant->y + yAction;
	ant->remainingSteps--;

	// If there is food, increment the ant's total food count.
	if(ant->x>=0 && ant->x<arenaSize && ant->y>=0 && ant->y<arenaSize) {
		if(arena[ant->x][ant->y]=='*')
			ant->numFood++;
	}
	else {
		ant->x = ant->x - xAction;
		ant->y = ant->y - yAction;
	}

	arena[ant->x][ant->y] = '$';
	
	printf("Food count: %d\n", ant->numFood);

	printArena(arena);
	delay(100);

	action(arena, ant);
}

int main() {
	char arena[arenaSize][arenaSize];
	ptrToAnt myAnt = hatchAnt();

	setArena(arena); 
	arena[myAnt->x][myAnt->y] = '$';
	printArena(arena);
	delay(100);
	action(arena, myAnt);

	return 0;
}
