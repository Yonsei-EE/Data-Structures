#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int add(int x, int y) {
	return x + y;
}

int sub(int x, int y) {
	return x - y;
}

int mul(int x, int y) {
	return x * y;
}

double div(int x, int y) {
	return (double) x / (double) y;
}

int main(void) {
	int x, y;
	char op;
	scanf("%c %d %d", &op, &x, &y);

	if (op == '+') {
		printf("%d", add(x, y));
	}
	else if (op == '-') {
		printf("%d", sub(x, y));
	}
	else if (op == '*') {
		printf("%d", mul(x, y));
	}
	else if (op == '/') {
		printf("%.1f", div(x, y));
	}
	else {
		printf("error");
	}

	return 0;
}