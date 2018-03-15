#define _CRT_SECURE_NO_WARNINGS

#define PI 3.14159265359

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// this program transforms a omnidirectional image to a panoramic image
// the center of view, outermost radius and innermost radius of the desired omnidirectional image are known

void main()
{
	FILE *out, *in;
	unsigned char *buffer, *buffout;
	short targaheader[9] = {0, 2, 0, 0, 0, 0, 111, 222, 8216};
	unsigned char sname[100];
	unsigned char temp;
	short width, height, wedges, layers;
	int nextRowBuffer, nextRowBuffout, sizeOfBuffer, sizeOfBuffout;
	int i, j, k, x, y, p, s;

	double originX, originY, outerMostR, innerMostR;
	double R;
	
	in = fopen("original.tga", "rb");
        fread(targaheader, sizeof(targaheader), 1, in);
	
	// settings for omni image.. 640x480
	originX = 344.0;	// the center of view is set.. (344, 227)px
        originY = 227.0;
	outerMostR = 185.0;     // the outermost radius and innermost radius is set.. 25~185px
        innerMostR = 25.0;
	width = targaheader[6];
	height = targaheader[7];
	nextRowBuffer = width * 3;
	sizeOfBuffer = width * height * 3;
	buffer = (unsigned char *)malloc(sizeOfBuffer + 1);
	fread(buffer, sizeOfBuffer, 1, in);
	fclose(in);
	
	// settings for pano image.. 360x115
	wedges = 360;	// the sampling rate for each circle layer is set.. 360px
	layers = (int)log(outerMostR / innerMostR) / log((wedges + PI) / (wedges - PI)) + 1;
			// # of circle layers in reference to the sampling rate
	nextRowBuffout = wedges * 3;
	sizeOfBuffout = layers * wedges * 3;
	buffout = (unsigned char *)malloc(sizeOfBuffout + 1);	

	// scan pano image grid and collect corresponding omni pixels
	for (p = 0; p < layers; p++)
	{
		for (k = nextRowBuffout*p; k < nextRowBuffout*(p + 1); k += 3)
		{
			// calculate pano pixel coordinates for readability
			s = (k%nextRowBuffout) / 3;

			// calculate corresponding omni coordinates
			R = exp(p*log((wedges + PI) / (wedges - PI)))*innerMostR;
			x = R*cos(2 * PI*s / wedges);
			y = R*sin(2 * PI*s / wedges);
			j = (x + originX) * 3;
			i = y + originY;

			// collect omni pixels
			buffout[k] = buffer[j + i*nextRowBuffer];
			buffout[k + 1] = buffer[j + i*nextRowBuffer + 1];
			buffout[k + 2] = buffer[j + i*nextRowBuffer + 2];
		}
	}

	// write output picture
	out = fopen("buffout.tga", "wb");
	targaheader[6] = wedges;
	targaheader[7] = layers;
	fwrite(targaheader, sizeof(targaheader), 1, out);
	fwrite(buffout, sizeOfBuffout, 1, out);
	fclose(out);
	free(buffer);
	free(buffout);
}
 
