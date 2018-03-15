#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

struct Student {
	char name[100];
	unsigned long number;
	int score1;
	int score2;
	int total;
};

// Takes in array of values and gives out the average of the values.
float avr(int *values, int size) {
	int i;
	float avr = 0;
	
	for (i = 0; i < size; i++) {
		avr += values[i];
	}
	avr /= size;

	return avr;
}

int main() {
	int i, j;
	float avrScore1, avrScore2, avrTotal;
	char num[3] = "1";
	struct Student students[5];
	FILE *fp;

	// Read files and store the data in the structure array
	for (i = 0; i < 5; i++, num[0]++) {
		char fileName[15] = "Student_";
		strcat(fileName, num);
		strcat(fileName, ".txt");

		fopen_s(&fp, fileName, "r");
		if (fp == NULL) {
			printf("Could not find file.");
		}

		fscanf(fp, "%[^\t]%lu%d%d", students[i].name, &students[i].number, &students[i].score1, &students[i].score2);
		students[i].total = students[i].score1 + students[i].score2;

		fclose(fp);
	}

	// Average the data
	int temp[5];
	for (i = 0; i < 5; i++) {
		temp[i] = students[i].score1;
	}
	avrScore1 = avr(temp, 5);
	for (i = 0; i < 5; i++) {
		temp[i] = students[i].score2;
	}
	avrScore2 = avr(temp, 5);
	for (i = 0; i < 5; i++) {
		temp[i] = students[i].total;
	}
	avrTotal = avr(temp, 5);

	// Write the result
	fp = fopen("Check List.txt", "w");

	fprintf(fp, "Student name\tStudent number\tScore1\tScore2\tTotal\n");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "%s\t%lu\t%d\t%d\t%d\n", students[i].name, students[i].number, students[i].score1, students[i].score2, students[i].total);
	}
	fprintf(fp, "----------\t----------\t%.2lf\t%.2lf\t%.2lf", avrScore1, avrScore2, avrTotal);

	fclose(fp);

	return 0;
}