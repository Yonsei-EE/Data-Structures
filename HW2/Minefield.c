#define N 8

#include <stdio.h>

int main(){
	int field[N][N];
	int x, y, i, j;
	int num = 0;

	// Initialize minefield
	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++)
			field[x][y] = 0;
	}

	// Get # of mines (5~35)
	while (num < 5 || num > 35) {
		printf("Number of mines (5~35) : ");
		scanf("%d", &num);
	}

	// Scatter mines
	while (num > 0) {
		x = (int)(rand() % N);
		y = (int)(rand() % N);
		if (field[x][y] >= 0) {
			field[x][y] = -1;
			num--;
		}
	}

	// Increment all blocks adjacent to each mine
	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++)
			if (field[x][y] < 0) {
				for (i = x - 1; i <= x + 1; i++) {
					if (field[i][y - 1] >= 0) field[i][y - 1]++;
					if (field[i][y + 1] >= 0) field[i][y + 1]++;
				}
				if (field[x - 1][y] >= 0) field[x - 1][y]++;
				if (field[x + 1][y] >= 0) field[x + 1][y]++;
			}
	}

	// Print minefield
	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++) {
			if (field[x][y] >= 0)
				printf("%d", field[x][y]);
			else
				putchar('*');
		}
		putchar('\n');
	}

	return 0;
}