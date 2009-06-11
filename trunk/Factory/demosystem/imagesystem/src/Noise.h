#ifndef NOISE_H__
#define NOISE_H__

#include <math.h>
#include <stdlib.h>
//#include "FreeImage.h"

// Prime numbers for random number generation
#define prime1 15731
#define prime2 789221
#define prime3 1376312589

class Noise
{
public:
	static float linearInterpolator(float v1, float v2, float x);
	static float cosineInterpolator(float v1, float v2, float x);
	static float cubicInterpolator(float v0, float v1, float v2, float v3, float x);
	static void  setSeed(unsigned int seed);
	static void  setPrimes(unsigned int p1, unsigned int p2, unsigned int p3);
	static float noise1D(int x);
	static float noise2D(int x, int y);
	static float noise3D(int x, int y, int z);
	static float smoothNoise1D(int x);
	static float smoothNoise2D(int x, int y);
	static float smoothNoise3D(int x, int y, int z);
	static float interpolatedNoise1D(float x);
	static float interpolatedNoise2D(float x, float y);
	static float interpolatedNoise3D(float x, float y, float z);
	static float perlinNoise1D(float x, float ifreq, float persistence, int octaves);
	static float perlinNoise2D(float x, float y, float ifreq, float persistence, int octaves);
	static float perlinNoise3D(float x, float y, float z, float ifreq, float persistence, int octaves);
};
#endif
