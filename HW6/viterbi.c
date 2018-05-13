#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "binheap.h"

// Set structure for Trellis Diagram
struct IOcell {
	int output[2];
	int input;
};

// Global variables
int TrellisLookup[8][2];
int numNodes=1;
struct IOcell Trellis[8][8];
int sequenceLength;
double output[100][2];
	
// Create Node for priority queue
PtrToCell createNode(PtrToCell Parent, double cost, int state, int sequence) {
	PtrToCell newNode = malloc(sizeof(struct Cell));
	newNode->F = cost;
	newNode->Parent = Parent;
	newNode->x = state;
	newNode->y = sequence;
}

// Uniform Cost Search to find path with minimal total Euclidean Distance
PtrToCell exploreNode(PriorityQueue fringe) {
	int i, x, sequence;
	double cost;
	PtrToCell currentNode, newNode;
	if(!IsEmpty(fringe))
	{
		numNodes--;
		currentNode = GetMin(fringe);
	}
	else
		return NULL;

	x = currentNode->x;
	sequence = currentNode->y;
	
	if(sequence == sequenceLength)
		return currentNode;	

	// For each state we explore the two possible paths
	for(i=0; i<2; i++) {
		cost = currentNode->F;
		cost += sqrt(pow((double)Trellis[x][TrellisLookup[x][i]].output[0]-output[sequence][0],2) \
				+ pow((double)Trellis[x][TrellisLookup[x][i]].output[1]-output[sequence][1],2));	
		newNode = createNode(currentNode, cost, TrellisLookup[x][i], sequence+1);
		Insert(newNode, fringe);
	}

	return exploreNode(fringe);
}

// Once goal sequence is reached we retrace our steps to find the final path
void findInput(PtrToCell goal) {
	int x;
	PtrToCell parent = goal;
	printf("Processed Signal\n");
	while(parent->Parent!=NULL) {
		x = parent->x;
		parent = parent->Parent;
		printf("%d %d\n", Trellis[parent->x][x].output[0], Trellis[parent->x][x].output[1]);
	}
	parent = goal;
	printf("\nEstimated Input Signal\n");
	while(parent->Parent!=NULL) {
		x = parent->x;
		parent = parent->Parent;
		printf("%d ", Trellis[parent->x][x].input);
	}
	printf("\n\n");
}

int main() {
	int i=0;
	// Trellis Diagram Lookup table. This table gives the two next states for a given state.
	TrellisLookup[0][0] = 0;
	TrellisLookup[0][1] = 4;
	TrellisLookup[1][0] = 0;
	TrellisLookup[1][1] = 4;
	TrellisLookup[2][0] = 1;
	TrellisLookup[2][1] = 5;
	TrellisLookup[3][0] = 1;
	TrellisLookup[3][1] = 5;
	TrellisLookup[4][0] = 2;
	TrellisLookup[4][1] = 6;
	TrellisLookup[5][0] = 2;
	TrellisLookup[5][1] = 6;
	TrellisLookup[6][0] = 3;
	TrellisLookup[6][1] = 7;
	TrellisLookup[7][0] = 3;
	TrellisLookup[7][1] = 7;

	// Trellis Diagram. This diagram gives the output and input of a transition.
	Trellis[0][0].output[0] = 0;
	Trellis[0][0].output[1] = 0;
	Trellis[0][0].input = 0;
	Trellis[0][4].output[0] = 1;
	Trellis[0][4].output[1] = 1;
	Trellis[0][4].input = 1;
	Trellis[1][0].output[0] = 0;
	Trellis[1][0].output[1] = 1;
	Trellis[1][0].input = 1;
	Trellis[1][4].output[0] = 1;
	Trellis[1][4].output[1] = 0;
	Trellis[1][4].input = 0;
	Trellis[2][1].output[0] = 0;
	Trellis[2][1].output[1] = 0;
	Trellis[2][1].input = 0;
	Trellis[2][5].output[0] = 1;
	Trellis[2][5].output[1] = 1;
	Trellis[2][5].input = 1;
	Trellis[3][1].output[0] = 0;
	Trellis[3][1].output[1] = 1;
	Trellis[3][1].input = 1;
	Trellis[3][5].output[0] = 1;
	Trellis[3][5].output[1] = 0;
	Trellis[3][5].input = 0;
	Trellis[4][2].output[0] = 0;
	Trellis[4][2].output[1] = 0;
	Trellis[4][2].input = 1;
	Trellis[4][6].output[0] = 1;
	Trellis[4][6].output[1] = 1;
	Trellis[4][6].input = 0;
	Trellis[5][2].output[0] = 0;
	Trellis[5][2].output[1] = 1;
	Trellis[5][2].input = 0;
	Trellis[5][6].output[0] = 1;
	Trellis[5][6].output[1] = 0;
	Trellis[5][6].input = 1;
	Trellis[6][3].output[0] = 0;
	Trellis[6][3].output[1] = 0;
	Trellis[6][3].input = 1;
	Trellis[6][7].output[0] = 1;
	Trellis[6][7].output[1] = 1;
	Trellis[6][7].input = 0;
	Trellis[7][3].output[0] = 0;
	Trellis[7][3].output[1] = 1;
	Trellis[7][3].input = 0;
	Trellis[7][7].output[0] = 1;
	Trellis[7][7].output[1] = 0;
	Trellis[7][7].input = 1;

	// Choose signal : noisefree or noise corrupted
	FILE *fp;
	// fp = fopen("Noisecorrupted_outputsignal.txt", "r");
	fp = fopen("Noisefree_outputsignal.txt", "r");
	while(!feof(fp)) {
		fscanf(fp, "%lf\t%lf", &output[i][0], &output[i][1]);
		i++;
	}

	// Print signal info
	sequenceLength = i-1;
	printf("Sequence Length: %d\n", sequenceLength);
	printf("\nReceived Signal\n");
	for(i=sequenceLength-1; i>=0; i--) {
		printf("%lf %lf\n", output[i][0], output[i][1]);
	}	
	printf("\n");
	
	// Start search
	PriorityQueue fringe = Initialize(200000);
	PtrToCell startNode, temp;

	startNode = createNode(NULL,0,0,0);
	Insert(startNode, fringe);
	temp = exploreNode(fringe);

	// If successful, print result
	if(temp!=NULL)
		findInput(temp);
	else
		printf("failure..");

	return 0;
}


