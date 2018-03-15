#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "list.h"

int findGreatestPrime(n) {
	int flag, i;

	while (1) {
		for (flag = 0, i = 2; i < n; i++) {
			if (n % i == 0) {
				flag = 1;
				break;
			}
		}
		if (!flag) break;
		n--;
	}
	
	return n;
}

int main() {
	int i, j, n, p;
	int flag = 0, count = 0, sum = 0, iterations = 0;
	List L = NULL;
	Position P, lastP;

	// Get natural number (We will find all prime numbers smaller than this number)
	scanf("%d", &n);

	clock_t tik = clock();

	// Initialize list
	L = MakeEmpty(L);
	P = L;

	// Insert the first prime number, 2, to get things started
	Insert(2, L, P);
	lastP = P->Next;
	count++;
	sum += 2;

	// Quickly find nearest prime number to sqrt(n)
	p = (int)sqrt((double)n);
	p = findGreatestPrime(p);

	// Find all prime numbers by dividing by prime numbers in the list. The list is updated in realtime.
	for (i = 3; i < n; i++) {
		P = L;
		flag = 0;

		while (P->Next != NULL && P->Next->Element <= p) {
			P = Advance(P);
			iterations++;
			if (i % P->Element == 0) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			Insert(i, L, lastP);
			lastP = lastP->Next;
			count++;
			sum += i;
		}
	}

	clock_t tok = clock();

	// Voilà! A very efficient algorithm to find prime numbers without a predetermined list.
	printf("iterations : %d\nTime taken: %.2fms\n# of prime numbers : %d\nsum of prime numbers : %d\n", iterations, (double)(tok - tik) / (CLOCKS_PER_SEC / 1000), count, sum);

	return 0;
}