#include <stdio.h>

void upsidedownPiramid() {
	int i, j;
	char alphabet = 'a';

	for (i = 26; i > 0; i--) {
		for (j = i; j > 0; j--) {
			printf("%c", alphabet);
		}
		alphabet = alphabet + 1;
		printf("\n");
	}
}

void rightsideupPiramid() {
	int i, j;
	char alphabet = 'a';

	for (i = 0; i < 26; i++) {
		for (j = i; j < 26; j++) {
			printf(" ");
		}
		for (j = 0; j < i + 1; j++) {
			printf("%c", alphabet);
		}
		alphabet = alphabet + 1;
		printf("\n");
	}
}

int main() {
	printf("(a)\n\n");
	upsidedownPiramid();
	printf("\n\n(b)\n");
	rightsideupPiramid();

	return 0;
}