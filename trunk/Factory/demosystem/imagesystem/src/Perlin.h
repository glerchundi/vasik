#ifndef PERLIN_H__
#define PERLIN_H__

#include "TVasik.h"
#include "Noise.h"

#include "FreeImage.h"

class Perlin
{
public:
	static void doit(FIBITMAP *bitmap, float ifreq, float persistence, int octaves);
};

#endif
