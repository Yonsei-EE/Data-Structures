#define numMembers 37

#include <stdio.h>
#include <string.h>
#include "list.h"
#include "stack.h"
#include "binheap.h"

void buildAdjacencyMatrix(FILE *fp, int matrix[numMembers][numMembers]) {
	int i, j, member1, member2, intimacy;

	for(i=0; i<numMembers; i++) {
		for(j=0; j<numMembers; j++) {
			matrix[i][j] = 0;
		}
	}

	while(!feof(fp)) {
		fscanf(fp, "%d%d%d", &member1, &member2, &intimacy);
		matrix[member1][member2] = intimacy;
		matrix[member2][member1] = intimacy;
	}
}

void printMatrix(int matrix[numMembers][numMembers], char members[numMembers][2][20]) {
	int i, j;

	for(i=0; i<numMembers; i++)
		printf("%s: %s\n", members[i][1], members[i][0]);

	printf("\n    ");
	for(i=0; i<numMembers; i++)
		printf("%s ", members[i][1]);	
	putchar('\n');
	for(i=0; i<numMembers; i++) {
		printf("%s ", members[i][1]);
		for(j=0; j<numMembers; j++) {
			printf(" %d  ", matrix[i][j]);
		}
		printf("\n");
	}
}

List findPopularByMatrix(int matrix[numMembers][numMembers]) {
	int i, j, count=0, max=-1;
	List MrPopular = NULL;

	for(i=0; i<numMembers; i++) {
		for(j=0; j<numMembers; j++) {
			if(matrix[i][j]!=0)
				count++;
		}
		if(count>max) {
			max = count;
			MrPopular = MakeEmpty(MrPopular);
			Insert(i, 0, MrPopular, MrPopular);
		}
		else if(count==max) 
			Insert(i, 0, MrPopular, MrPopular);
		count=0;
	}

	return MrPopular;
}

void printSubGroup(List visited, char members[numMembers][2][20]) {
	Position P;

	P = visited->Next;
	while(P!=NULL){
		printf("%s ", members[RetrieveElement(P)][1]);
		P = Advance(P);
	}
	printf("\n");
}	

void dfsFindSubGroup(int matrix[numMembers][numMembers], Stack fringe, List visited, char members[numMembers][2][20]) {
	int i, j, success;
	PtrToCell currentCell, newCell;

	currentCell = PopStack(fringe);
	printf("%s ", members[currentCell->member][1]);

	for(i=0; i<numMembers; i++) {
		if(Find(i, visited)==NULL && matrix[currentCell->member][i]!=0) {
			newCell = CreateCell(i,currentCell);
			Push(newCell, fringe);
			Insert(i, 0, visited, visited);
		}
	}
	
	if(!StackIsEmpty(fringe))
		dfsFindSubGroup(matrix, fringe, visited, members);
}	

void dfsFindSubGroups(int matrix[numMembers][numMembers], char members[numMembers][2][20]) {
	Stack fringe = CreateStack();
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToCell initCell = CreateCell(i,NULL);
			Push(initCell,fringe);
			Insert(i, 0, visited, visited);
			dfsFindSubGroup(matrix, fringe, visited, members);
			putchar('\n');

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}

void bfsFindSubGroup(int matrix[numMembers][numMembers], PriorityQueue fringe, List visited) {
	int i, j=0, success;
	PtrToQueueCell currentCell, newCell;

	currentCell = GetMin(fringe);

	for(i=0; i<numMembers; i++) {
		if(Find(i, visited)==NULL && matrix[currentCell->member][i]!=0) {
			newCell = CreateQueueCell(j++,i,currentCell);
			InsertQueue(newCell, fringe);
			Insert(i, 0, visited, visited);
		}
	}
	
	if(!QueueIsEmpty(fringe))
		bfsFindSubGroup(matrix, fringe, visited);
}	


void bfsFindSubGroups(int matrix[numMembers][numMembers], char members[numMembers][2][20]) {
	PriorityQueue fringe = Initialize(100);
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToQueueCell initCell = CreateQueueCell(0,i,NULL);
			InsertQueue(initCell,fringe);
			Insert(i, 0, visited, visited);
			bfsFindSubGroup(matrix, fringe, visited);
			printSubGroup(visited, members);

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}

void iteratedDeepening(int matrix[numMembers][numMembers], Stack fringe, List visited, char members[numMembers][2][20]) {
	int i, j, success;
	PtrToCell currentCell, newCell;

	currentCell = PopStack(fringe);

	for(i=0; i<numMembers; i++) {
		if(Find(i, visited)==NULL && matrix[currentCell->member][i]!=0) {
			newCell = CreateCell(i,currentCell);
			Push(newCell, fringe);
			Insert(i, 0, visited, visited);
		}
	}
	
	if(!StackIsEmpty(fringe))
		iteratedDeepening(matrix, fringe, visited, members);
}	

void idsFindSubGroups(int matrix[numMembers][numMembers], char members[numMembers][2][20]) {
	Stack fringe = CreateStack();
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToCell initCell = CreateCell(i,NULL);
			Push(initCell,fringe);
			Insert(i, 0, visited, visited);
			iteratedDeepening(matrix, fringe, visited, members);
			printSubGroup(visited, members);

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}


void buildAdjacencyList(FILE *fp, List list[numMembers]) {
	int i, member1, member2, intimacy;
	
	for(i=0; i<numMembers; i++) {
		list[i] = NULL;
		list[i] = MakeEmpty(list[i]);
	}

	while(!feof(fp)) {
		fscanf(fp, "%d%d%d", &member1, &member2, &intimacy);
		Insert(member2, intimacy, list[member1], list[member1]);	
		Insert(member1, intimacy, list[member2], list[member2]);
	}
}

void printList(List list[numMembers], char members[numMembers][2][20]) {
	int i;
	Position P;

	for(i=0; i<numMembers; i++) {
		printf("%s\t", members[i][1]);
		P = First(list[i]);
		while(P!=NULL) {
			printf("%s ", members[RetrieveElement(P)][1]);
			P = Advance(P);
		}
		putchar('\n');
	}
}

List findPopularByList(List list[numMembers]) {
	int i, count=0, max=-1;
	List MrPopular = NULL;
	Position P;

	for(i=0; i<numMembers; i++) {
		P = First(list[i]);
		while(P!=NULL) {
			count++;
			P = Advance(P);
		}
		if(count>max) {
			max = count;
			MrPopular = MakeEmpty(MrPopular);
			Insert(i, 0, MrPopular, MrPopular);
		}
		else if(count==max) 
			Insert(i, 0, MrPopular, MrPopular);
		count=0;
	}

	return MrPopular;
}

void dfsFindSubGroup2(List list[numMembers], Stack fringe, List visited, char members[numMembers][2][20]) {
	int i, j, success;
	PtrToCell currentCell, newCell;
	Position P;

	currentCell = PopStack(fringe);
	printf("%s ", members[currentCell->member][1]);

	for(P = First(list[currentCell->member]); P!=NULL; P=Advance(P)) {
		if(Find(RetrieveElement(P), visited)==NULL) {
			newCell = CreateCell(RetrieveElement(P),currentCell);
			Push(newCell, fringe);
			Insert(RetrieveElement(P), 0, visited, visited);
		}
	}
	
	if(!StackIsEmpty(fringe))
		dfsFindSubGroup2(list, fringe, visited, members);
}	

void dfsFindSubGroups2(List list[numMembers], char members[numMembers][2][20]) {
	Stack fringe = CreateStack();
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToCell initCell = CreateCell(i,NULL);
			Push(initCell,fringe);
			Insert(i, 0, visited, visited);
			dfsFindSubGroup2(list, fringe, visited, members);
			putchar('\n');

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}

void bfsFindSubGroup2(List list[numMembers], PriorityQueue fringe, List visited) {
	int i, j=0, success;
	PtrToQueueCell currentCell, newCell;
	Position P;

	currentCell = GetMin(fringe);

	for(P = First(list[currentCell->member]); P!=NULL; P=Advance(P)) {
		if(Find(RetrieveElement(P), visited)==NULL) {
			newCell = CreateQueueCell(j++,RetrieveElement(P),currentCell);
			InsertQueue(newCell, fringe);
			Insert(RetrieveElement(P), 0, visited, visited);
		}
	}
	
	if(!QueueIsEmpty(fringe))
		bfsFindSubGroup2(list, fringe, visited);
}	


void bfsFindSubGroups2(List list[numMembers], char members[numMembers][2][20]) {
	PriorityQueue fringe = Initialize(100);
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);
	Position P;

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToQueueCell initCell = CreateQueueCell(0,i,NULL);
			InsertQueue(initCell,fringe);
			Insert(i, 0, visited, visited);
			bfsFindSubGroup2(list, fringe, visited);
			printSubGroup(visited, members);

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}

void iteratedDeepening2(List list[numMembers], Stack fringe, List visited, char members[numMembers][2][20]) {
	int i, j, success;
	PtrToCell currentCell, newCell;
	Position P;

	currentCell = PopStack(fringe);

	for(P = First(list[currentCell->member]); P!=NULL; P=Advance(P)) {
		if(Find(RetrieveElement(P), visited)==NULL) {
			newCell = CreateCell(RetrieveElement(P),currentCell);
			Push(newCell, fringe);
			Insert(RetrieveElement(P), 0, visited, visited);
		}
	}
	
	if(!StackIsEmpty(fringe))
		iteratedDeepening2(list, fringe, visited, members);
}	

void idsFindSubGroups2(List list[numMembers], char members[numMembers][2][20]) {
	Stack fringe = CreateStack();
	List visited =NULL, totalVisited=NULL;
	visited = MakeEmpty(visited);
	totalVisited = MakeEmpty(totalVisited);

	for(int i=0; i<numMembers; i++) {
		if(Find(i, totalVisited)==NULL) {
			PtrToCell initCell = CreateCell(i,NULL);
			Push(initCell,fringe);
			Insert(i, 0, visited, visited);
			iteratedDeepening2(list, fringe, visited, members);
			printSubGroup(visited, members);

			while(!IsEmpty(visited))
				Insert(Pop(visited),0,totalVisited, totalVisited);
		}
	}
}


int main() {
	int i, adMatrix[numMembers][numMembers];
	char members[numMembers][2][20], memberName[20], abbrev[4];
	List adList[numMembers], MrPopular;
	FILE *fp;

	// read member names
	fp = fopen("memberList.txt", "r");
	if(fp==NULL) {
		printf("Could not find file.");
		return 1;
	}

	while(EOF != fscanf(fp, "%d\t%[^\t]\t%[^\n]\n", &i, memberName, abbrev)) {
		strcpy(members[i][0], memberName);
		strcpy(members[i][1], abbrev);
	}

	fclose(fp);

	//////////////////////////////////////////////////////////////////////
	// Adjacency Matrix
	//////////////////////////////////////////////////////////////////////

	// read intimacy info
	fp = fopen("intimacy.txt", "r");
	if(fp==NULL) {
		printf("Could not find file.");
		return 1;
	}

	buildAdjacencyMatrix(fp, adMatrix);
	printMatrix(adMatrix, members);
	putchar('\n');
	
	// Find most popular
	MrPopular = findPopularByMatrix(adMatrix);
	i = 0;
	while(!IsEmpty(MrPopular)) {
		if(i>0)
			printf(", ");
		printf("%s", members[RetrieveElement(First(MrPopular))][0]);
		Pop(MrPopular);
		i++;
	}	
	if(i>1)
		printf(" are");
	else
		printf(" is");
	printf(" most popular!\n\n");

	// Find subGroup
	printf("DFS\n");
	dfsFindSubGroups(adMatrix, members); 
	printf("\nBFS\n");
	bfsFindSubGroups(adMatrix, members);
	printf("\nIDS\n");
	idsFindSubGroups(adMatrix, members);

	fclose(fp);

	//////////////////////////////////////////////////////////////////////
	// Adjacency List
	//////////////////////////////////////////////////////////////////////

	printf("----------------------------------------------------------------\n");
	// read intimacy info
	fp = fopen("intimacy.txt", "r");
	if(fp==NULL) {
		printf("Could not find file.");
		return 1;
	}

	buildAdjacencyList(fp, adList);
	putchar('\n');
	printList(adList, members);
	putchar('\n');

	// find most popular
	MrPopular = findPopularByList(adList);
	i = 0;
	while(!IsEmpty(MrPopular)) {
		if(i>0)
			printf(", ");
		printf("%s", members[RetrieveElement(First(MrPopular))][0]);
		Pop(MrPopular);
		i++;
	}	
	if(i>1)
		printf("are");
	else
		printf(" is");
	printf(" most popular!\n\n");

	// Find subGroup
	printf("DFS\n");
	dfsFindSubGroups2(adList, members); 
	printf("\nBFS\n");
	bfsFindSubGroups2(adList, members);
	printf("\nIDS\n");
	idsFindSubGroups2(adList, members);

	return 0;
}
