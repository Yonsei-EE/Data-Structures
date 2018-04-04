#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	FILE *out, *in;
	unsigned char *buffer, *buffout, *gray;
	short targaheader[9] = { 0,2,0,0,0,0,111,222,8216 };
	unsigned char sname[100];
	unsigned char temp;
	int width, height, bRow, bCol, gRow, gCol, i, j, k, size, gx, gy;
	int t, max = 0, min = 1500;

	in = fopen("Images/original2.tga", "rb");
	// read first the header component
	fread(targaheader, sizeof(targaheader), 1, in);
	width = targaheader[6];  // read picture width
	bCol = width * 3;	// # of columns of buffer array
	gCol = width + 2;	// # of columns of gray array
	height = targaheader[7]; // read picture height
	bRow = height;		// # of rows of buffer array 
	gRow = height + 2;	// # of rows of gray array
	size = width*height * 3;
	buffer = (unsigned char *)malloc(bCol*bRow);
	fread(buffer, width * height * 3, 1, in);
	fclose(in);

	// We allocate space for a padded gray scale image
	gray = (unsigned char *)malloc(gCol*gRow);
	buffout = (unsigned char *)malloc(bCol*bRow);

	// Set Padding
	for (i = 0; i < gRow*gCol; i++)
		gray[i] = 0;

	// Get gray image
	for (i = 0, j = gCol + 1; i < bCol*bRow; i += 3, j++) {
		temp = buffer[i] * 0.3 + buffer[i + 1] * 0.6 + buffer[i + 2] * 0.1;

		if (j % gCol == gCol - 1)
			j = j + 2;
		gray[j] = temp;
	}

	// Sobel filter
	for (i = 0, j = width + 3; i < bCol*bRow; i += 3, j++) {
		if (j % gCol == gCol - 1)
			j = j + 2;

		gx =- 1 * gray[j - gCol - 1] + 0 * gray[j - gCol] + 1 * gray[j - gCol + 1]
			- 2 * gray[j - 1] + 0 * gray[j] + 2 * gray[j + 1]
			- 1 * gray[j + gCol - 1] + 0 * gray[j + gCol] + 1 * gray[j + gCol + 1];

		gy = - 1 * gray[j - gCol - 1] - 2 * gray[j - gCol] - 1 * gray[j - gCol + 1]
			+ 0 * gray[j - 1] + 0 * gray[j] + 0 * gray[j + 1]
			+ 1 * gray[j + gCol - 1] + 2 * gray[j + gCol] + 1 * gray[j + gCol + 1];

		t = sqrt(gx*gx + gy*gy);
		temp = t;

		buffout[i] = buffout[i + 1] = buffout[i + 2] = temp;
	}

	// write output picture
	out = fopen("Images/test2.tga", "wb");
	fwrite(targaheader, sizeof(targaheader), 1, out);
	fwrite(buffout, width * height * 3, 1, out);
	fclose(out); free(buffer); free(buffout);

	return 0;
}
