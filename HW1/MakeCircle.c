#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

void paint(int x, int y, double r) {
	if (pow(x - r, 2) + pow(y - r, 2) <= (pow(r, 2))) {
		printf("* ");
	}
	else {
		printf("  ");
	}
}

int main() {
	double r;
	int x, y, d;

	printf("Enter radius : ");
	scanf("%lf", &r);
	d = (int) (2 * r);

	for (y = 0; y < d + 1; y++) {
		for (x = 0; x < d + 1; x++) {
			paint(x, y, r);
		}
		printf("\n");
	}
}