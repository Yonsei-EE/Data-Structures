#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

double determinant(double a, double b, double c) {
	return pow(b, 2) - 4 * a * c;
}

void secondOrder(double a, double b, double c) {
	double x1, x2, D;
	D = determinant(a, b, c);

	if (D >= 0) {
		x1 = (-b - sqrt(D)) / (2 * a);
		x2 = (-b + sqrt(D)) / (2 * a);
		printf("x1 = %.2lf, x2 = %.2lf", x1, x2);
	}
	else {
		D = -D;
		x1 = -b / (2 * a);
		x2 = sqrt(D) / (2 * a);
		printf("x1 = %.2lf - %.2lfi, x2 = %.2lf + %.2lfi", x1, x2, x1, x2);
	}
}

int main() {
	double a, b, c;

	scanf("%lf %lf %lf", &a, &b, &c);
	if (a != 0) {
		secondOrder(a, b, c);
	}
	else if (b != 0) {
		printf("x1 = %.2lf", -c / b);
	}
	else {
		printf("Real Number");
	}
}