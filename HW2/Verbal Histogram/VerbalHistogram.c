#include <stdio.h>
#include <math.h>
// We will use the integer values for each alphabet. In order to shorten the size of the array, we subtract each value by 65.
// a : 97 z : 122 A : 65 Z :90 -> a : 32 z : 57 A : 0 Z :25
int main() {
	int i, alphabet, max = 0;
	float mean = 0.0, s = 0.0;
	int histogram[58];
	char temp;
	FILE *fp;

	// Initialize histogram
	for (i = 0; i < 58; i++) {
		histogram[i] = 0;
	}

	// Open file
	fopen_s(&fp, "sample.txt", "r");
	if (fp == NULL) {
		printf("Could not find file.");
	}

	// For each character, match the integer value of the character with an alphabet and count the corresponding alphabet.
	while (!feof(fp)) {
		fscanf_s(fp, "%c", &temp);
		alphabet = (int)temp;
		alphabet -= 65;

		if(alphabet > -1 && alphabet < 58)
			histogram[alphabet]++;
	}

	fclose(fp);

	// Add the upper case letters with the lower case letters.
	for (i = 0; i < 26; i++) {
		histogram[i] += histogram[i + 32];
		if (histogram[i] > max)
			max = histogram[i];
	}

	for (i = 0; i < 26; i++) {
		mean += histogram[i];
	}
	mean /= 26;

	for (i = 0; i < 26; i++) {
		s += pow(histogram[i] - mean, 2);
	}
	s = sqrt(s / 26);

	// Print vertical histogram.
	for (i = max; i >= 1; --i)
	{
		for (int j = 0; j < 26; j++)
		{
			if (i <= histogram[j])
				printf(" * ");
			else
				printf("   ");
		}
		putchar('\n');
	}
	for (i = 65; i < 91; i++) {
		printf(" %c ", i);
	}
	printf("\nAverage : %.2f\nStand Deviation : %.2f\n", mean, s);

	return 0;
}