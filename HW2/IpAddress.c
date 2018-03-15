#include <stdio.h>
#include <math.h>

int binaryToDecimal(int n);
int decimalToBinary(int);

int main()
{
	int dec[4], bin[4];

	printf("Enter IP address in decimals : ");
	scanf("%d.%d.%d.%d", &dec[0], &dec[1], &dec[2], &dec[3]);

	for (int i = 0; i < 4; i++) {
		bin[i] = decimalToBinary(dec[i]);
		printf("%08d.", bin[i]);
	}
	printf("\b \n");

	printf("Enter IP address in binary : ");
	scanf("%d.%d.%d.%d", &bin[0], &bin[1], &bin[2], &bin[3]);

	for (int i = 0; i < 4; i++) {
		dec[i] = binaryToDecimal(bin[i]);
		printf("%d.", dec[i]);
	}
	printf("\b \n");

	return 0;
}

int binaryToDecimal(int bin)
{
	if (bin == 0) {
		return 0;
	}
	else {
		return bin % 10 + 2 * binaryToDecimal(bin / 10);
	}
}

int decimalToBinary(int dec)
{
	if (dec == 0) {
		return 0;
	}
	else {
		return dec % 2 + 10 * decimalToBinary(dec / 2);
	}
}