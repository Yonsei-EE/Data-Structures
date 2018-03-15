#include <stdio.h>

// Three step convolution algorithm based on graphical movement
double *conv1(double *A, double *B, int lenA, int lenB) {
	int n, k, nconv;
	double *y;

	nconv = lenA + lenB;
	y = (double*)calloc(nconv, sizeof(double));

	for (n = 0; n < nconv; n++) {
		y[n] = 0;
		if (n < lenA) {
			for (k = 0; k < n + 1; k++) {
				y[n] += A[k] * B[n - k];
			}
		}
		else if (n < lenB) {
			for (k = 0; k < lenA; k++) {
				y[n] += A[k] * B[n - k];
			}
		}
		else {
			for (k = n - lenB + 1; k < lenA; k++) {
				y[n] += A[k] * B[n - k];
			}
		}
	}

	return y;
}

// Simplified convolution
double *conv2(double *A, double *B, int lenA, int lenB)
{
	int nconv;
	int i, j, i1;
	double tmp;
	double *C;

	nconv = lenA + lenB - 1;
	C = (double*)calloc(nconv, sizeof(double));

	for (i = 0; i<nconv; i++)
	{
		i1 = i;
		tmp = 0.0;
		for (j = 0; j<lenB; j++)
		{
			if (i1 >= 0 && i1<lenA)
				tmp = tmp + (A[i1] * B[j]);

			i1 = i1 - 1;
			C[i] = tmp;
		}
	}

	return(C);
}

int main() {
	double x[100], h[100], *y;
	int n, k, j;

	// Initialize arrays
	for (n = 0; n < 100; n++) {
		if (n > 25 && n < 75) {
			x[n] = 1;
			h[n] = 0.5 * n;
		}
		else {
			x[n] = 0;
			h[n] = 0;
		}
	}

	// Perform Convolution
	y = conv1(&x, &h, 50, 100);

	// Print out result
	for (n = 0; n < 149; n++)
		printf("%5.2f ", y[n]);
	
	return 0;
}