#define _CRT_SECURE_NO_WARNINGS

#define PI 3.14159265359

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// this program transforms a panoramic image to a omnidirectional image
// the center of view, outermost radius and innermost radius of the desired omnidirectional image are known

void main()
{
	FILE *out, *in;
	unsigned char *buffer, *buffout;
	short targaheader[9] = { 0, 2, 0, 0, 0, 0, 111, 222, 8216 };
	short width, height, wedges, layers;
	int nextRowBuffer, nextRowBuffout, sizeOfBuffer, sizeOfBuffout;
	int i, j, k, x, y, p, s;

	double originX, originY, outerMostR, innerMostR;
	double R;

	in = fopen("panorama.tga", "rb");
        fread(targaheader, sizeof(targaheader), 1, in);


	// settings for omni image.. 640x480
	originX = 344.0;        // the center of view is set.. (344, 227)px
        originY = 227.0;
        outerMostR = 185.0;     // the outermost radius and innermost radius is set.. 25~185px
        innerMostR = 25.0;
	width = 640;
	height = 480;
	nextRowBuffout = width * 3;
	sizeOfBuffout = width * height * 3;
	buffout = (unsigned char *)malloc(sizeOfBuffout + 1);

	// settings for pano image.. 360x115
	wedges = 360.0;		// the sampling rate for each circle layer is set.. 360px
	layers = (int)log(outerMostR / innerMostR) / log((wedges + PI) / (wedges - PI)) + 1;	
				// # of circle layers in reference to the sampling rate
	nextRowBuffer = wedges * 3;	 
	sizeOfBuffer = layers * wedges * 3;
	buffer = (unsigned char *)malloc(sizeOfBuffer + 1);
	fread(buffer, sizeOfBuffer, 1, in);
	fclose(in);

	// scan omni image grid and collect corresponding pano pixels
	for (i = 0; i < height; i++)
	{
		for (j = nextRowBuffout * i; j < nextRowBuffout * (i + 1); j += 3)
		{
			// calculate relative omni coordinates for readability. 
			// the center of view is relatively set to (0, 0)
			x = j % nextRowBuffout / 3 - originX;
			y = i - originY;

			// scan dougnut area and collect corresponding pano pixels
			if (pow(x, 2) + pow(y, 2) < pow(outerMostR, 2) && pow(x, 2) + pow(y, 2) > pow(innerMostR, 2))
			{
				// calculate corresponding pano pixel coordinates
				R = sqrt(pow(x, 2) + pow(y, 2));
				p = log(R / innerMostR) / log((wedges + PI) / (wedges - PI));

				if (x != 0)
					s = wedges / (2 * PI) * atan((double)y / x);

				// resolve x == 0
				else {
					s = 90;
					if (y < 0)
						s += 180;
				}

				// resolve atan range restrictions
				if (s >= 0 && x < 0)
					s += 180;
				if (s < 0) {
					s += 360;
					if (x < 0)
						s -= 180;
				}

				// collect pano pixels
				k = (int)(s + p*wedges);
				buffout[j] = buffer[k * 3];
				buffout[j+1] = buffer[k * 3 + 1];
				buffout[j+2] = buffer[k * 3 + 2];
			}
		}
	}

	// write output picture
	out = fopen("buffout.tga", "wb");
	targaheader[6] = width;
	targaheader[7] = height;
	fwrite(targaheader, sizeof(targaheader), 1, out);
	fwrite(buffout, sizeOfBuffout, 1, out);
	fclose(out);
	free(buffer);
	free(buffout);
}
