#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#define N 100
#define PI 3.1415926535

// gets magnitude and phase of given data
float *FT(float *data, int k){
	int n;
	float real = 0.0, imag = 0.0;
	float X[2];	// X[0] = magnitude, X[1] = phase

	for (n = 0; n < N; n++) {
		real += cos(2 * PI*k*n / (float)N) * data[n];
		imag += -sin(2 * PI*k*n / (float)N) * data[n];
	}

	X[0] = sqrt(real*real + imag*imag);
	X[1] = atan2(imag, real) / PI*180.0;

	return X;
}

main()
{
	float data1[N], data2[N];
	int m, n, k;
	float real, imag;
	float mag, phase;
	float *temp;
	
	// data1 : sinusoidal wave, data2 : rectangular function
	for(m=0; m < N; m++) data1[m] = sin(2 *PI* 2*m / (float) N) + 2*cos(10*PI*m/ (float) N);
	for (m = 0; m < N; m++) if (m > 25 && m < 75) data2[m] = 1; else data2[m] = 0;

	// get magnitude and phase for both functions ranging from 0 ~ N-1
	printf("sinusoidal wave\n\n");
	for (k = 0; k < N; k++) {
		temp = FT(data1, k);
		mag = temp[0];
		phase = temp[1];
		printf("f = %d : mag : %f phase : %f\n", k, mag, phase);
	}

	printf("\nrectangular function\n\n");
	for (k = 0; k < N; k++) {
		temp = FT(data2, k);
		mag = temp[0];
		phase = temp[1];
		printf("f = %d : mag : %f phase : %f\n", k, mag, phase);
	}

}