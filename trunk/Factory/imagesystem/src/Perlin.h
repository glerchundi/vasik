#ifndef PERLIN_H__
#define PERLIN_H__

#include "FreeImage.h"

#include "TVasik.h"
#include "Noise.h"

class Perlin
{
public:
	static void doit(FIBITMAP *bitmap, float ifreq, float persistence, int octaves);
};

#endif
