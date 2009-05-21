#include "Perlin.h"

void Perlin::doit(FIBITMAP *bitmap, float ifreq, float persistence, int octaves)
{
	BYTE *bits,c;
	unsigned int width,height,i,j;
	
	width  = FreeImage_GetWidth(bitmap);
	height = FreeImage_GetHeight(bitmap);
	bits   = FreeImage_GetBits(bitmap);
	
	Noise::setSeed(227765);
	
	for(i = 0 ; i < height ; i++) {
		for(j = 0 ; j < width ; j++) {
			c = (BYTE)((1.0 + Noise::perlinNoise2D((float)i, (float)j, ifreq, persistence, octaves))*(255.0*0.5));
			if(c == 255 || c == 0)
				LOGTHIS("%i %i %f",i,j,Noise::perlinNoise2D((float)i, (float)j, ifreq, persistence, octaves));
			bits[FI_RGBA_RED  ] = c;
			bits[FI_RGBA_GREEN] = c;
			bits[FI_RGBA_BLUE ] = c;
			bits += 4;
		}
	}
}
