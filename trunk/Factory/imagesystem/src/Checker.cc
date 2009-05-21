#include "Checker.h"

void Checker::doit(FIBITMAP *bitmap, int repeatx, int repeaty)
{
	BYTE *bits,c;
	unsigned int width,height,i,j;
	
	width  = FreeImage_GetWidth(bitmap);
	height = FreeImage_GetHeight(bitmap);
	bits   = FreeImage_GetBits(bitmap);
	
	repeatx = (int)(width / repeatx);
	repeaty = (int)(height / repeaty);
	
	for(i = 0 ; i < height ; i++) {
		for(j = 0 ; j < width ; j++) {
			!(((j/repeatx)+(i/repeaty)) % 2) ? c = 0 : c = 255;
			
			bits[FI_RGBA_RED  ] = c;
			bits[FI_RGBA_GREEN] = c;
			bits[FI_RGBA_BLUE ] = c;
			bits += 4;
		}
	}
}
