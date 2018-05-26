#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "binheap.h"

#define lambda 4
int evenID = 2;
int oddID = 1;

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds);
}

PtrToCell createCell(int ID, int Fuel) {
	PtrToCell newCell = malloc(sizeof(struct Cell));
	newCell->ID = ID;
	newCell->Fuel = Fuel;
	newCell->F = 0;

	return newCell;
}

int factorial(int k) {
	int fact=1, i;

	for(i=1; i<=k; i++)
		fact=fact*i;

	return fact;
}

double poisson(int k) {
	return pow(lambda, k) * exp(-lambda) / factorial(k);
}

double uniform(int k) {
	return 0.25;
}
	

void addLanding(PriorityQueue H) {
	int i, k;
	double p = rand()%100*0.01, CDF=0;
	for(k=0; k<20; k++) {
		CDF += poisson(k);
		if(p<CDF) {
			for(i=0;i<k;i++) {
				Insert(createCell(evenID, rand()%5+1), H);
				evenID += 2;
			}
		break;
		}	 
	}
	printf("%d more planes await landing! : ", k);
}

void addTakeoff(PriorityQueue H) {
	int i, k;
	double p = rand()%100*0.01, CDF=0;
	for(k=0; k<4; k++) {
		CDF += uniform(k);
		if(p<CDF) {
			for(i=0;i<k;i++) {
				if(IsFull(H)) {
					k = i;
					break;
				}
				Insert(createCell(oddID, 50), H);
				oddID += 2;
			}
		break;
		}	 
	}
	printf("%d more planes await takeoff! : ", k);
}

int useFuel(PriorityQueue H, PriorityQueue E) {
	PtrToCell Emergency;
	int i, n;
	for(i=1; i<H->Size+1; i++) {
		H->Cells[i]->Fuel--;
		if(H->Cells[i]->Fuel==0) {
			if(!IsFull(E))
				Insert(H->Cells[i], E);
		}
	}

	for(i=1; i<E->Size+1; i++) {
		n = Findi(E->Cells[i]->ID, H);
		if(n!=-1)
			Delete(n, H);
	}

	if(IsFull(E))
		return 1;
	return 0;
}

int landPlanes(PriorityQueue runway[5], PriorityQueue landing, PriorityQueue E, PriorityQueue takeoff) {
	for(int i=4; i>=0; i--) {
		if(!IsFull(runway[i])) {
			if(i==4) {
				if(!IsEmpty(E))
					Insert(GetMin(E), runway[i]);
				else if(!IsEmpty(takeoff))
					Insert(GetMin(takeoff), runway[i]);
				else if(IsEmpty(runway[i])&&!IsEmpty(landing))
					Insert(GetMin(landing), runway[i]);
			}
			else if(!IsEmpty(E))
				Insert(GetMin(E), runway[i]);
			else if(!IsEmpty(takeoff))
				Insert(GetMin(takeoff), runway[i]);
			else if(!IsEmpty(landing))
				Insert(GetMin(landing), runway[i]);
		}
	}
	if(!IsEmpty(E))
		return 1;
	return 0;
}

void updateRunway(PriorityQueue runway[5]) {
	for(int i=0; i<5; i++) {
		if(!IsEmpty(runway[i]))
			GetMin(runway[i]);
	}
}

void updateTime(PriorityQueue landing, PriorityQueue takeoff, PriorityQueue runway[5]) {
	for(int i=0; i<5; i++) {
		for(int j=1; j<runway[i]->Size+1;j++)
			runway[i]->Cells[j]->F--;
	}
	for(int i=1; i<landing->Size+1; i++)
		landing->Cells[i]->F--;
	for(int i=1; i<takeoff->Size+1; i++)
		takeoff->Cells[i]->F--;
}

void printWait(PriorityQueue H) {
	if(IsEmpty(H))
		printf("0\n");
	else {
		int sum=0.0;
		for(int i=1; i<H->Size+1; i++)
			sum += H->Cells[i]->F;
		
		printf("%d\n", -sum/H->Size);
	}
}

int main() {
	int error;
	PriorityQueue landing = Initialize(1000);
	PriorityQueue takeoff = Initialize(10);
	PriorityQueue emergency = Initialize(6);
	PriorityQueue runway[5];
	runway[0] = Initialize(5);
	runway[1] = Initialize(5);
	runway[2] = Initialize(5);	
	runway[3] = Initialize(5);
	runway[4] = Initialize(5);

	while(1) {
		printf("---------------------------------------------------------\n");
		addLanding(landing);
		PrintQueue(landing);
		addTakeoff(takeoff);
		PrintQueue(takeoff);
		
		printf("average takeoff waiting time: ");
		printWait(takeoff);
		printf("average landing waiting time: ");
		printWait(landing);
		error = useFuel(landing, emergency);
		printf("emergency: ");
		PrintQueue(emergency);
		error += landPlanes(runway, landing, emergency, takeoff);
		if(error) {
			printf("\nToo many emergencies!\n");
			return 1;
		}
		for(int j=0;j<5;j++) {
			printf("runway%d: ", j);
			PrintQueue(runway[j]);
		}
		updateRunway(runway);
		updateTime(landing, takeoff, runway);
		putchar('\n');


		delay(500);
	}

	return 0;
}
