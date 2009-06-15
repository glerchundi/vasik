#include "Noise.h"

static unsigned int p[3] = {prime1,prime2,prime3};

float Noise::linearInterpolator(float a, float b, float x) {
	return (a*(1-x) + b*x);
}

float Noise::cosineInterpolator(float a, float b, float x) {
	float f = (1.0 - cos(x * (float)M_PI)) * 0.5;
	
	return (a*(1-f) + b*f);
}

float Noise::cubicInterpolator(float v0, float v1, float v2, float v3, float x) {
	float P, Q, R, S;
	
	P = (v3 - v2) - (v0 - v1);
	Q = (v0 - v1) - P;
	R = v2 - v0;
	S = v1;
	
	return (P*powf(x,3) + Q*powf(x,2) + R*x + S);
}

void  Noise::setSeed(unsigned int seed) {
	// Shitty way of creating random values within a range.
	// They should be primes for good randomness but...
	srand(seed);
	p[0] = 10000      + (rand()%100000);
	p[1] = 100000     + (rand()%1000000);
	p[2] = 1000000000 + (rand()%1000000000);
}

void  Noise::setPrimes(unsigned int p1, unsigned int p2, unsigned int p3) {
	p[0] = p1;
	p[1] = p2;
	p[3] = p3;
}

float Noise::noise1D(int x) {
    x = (x<<13) ^ x;
    
    return (float)( 1.0 - ( (x * (x * x * p[0] + p[1]) + p[2]) & 0x7fffffff) / 1073741824.0);   
}

float Noise::noise2D(int x, int y) {
	int n;
	
	n = x + y*57;
	n = (n<<13) ^ n;
	
	return (float)( 1.0 - ( (n * (n * n * p[0] + p[1]) + p[2]) & 0x7fffffff ) / 1073741824.0);
}	

float Noise::noise3D(int x, int y, int z) {
	int n;
	
	n = x + y*57 + z;
	n = (n<<13) ^ n;
	
	return (float)( 1.0 - ( (n * (n * n * p[0] + p[1]) + p[2]) & 0x7fffffff ) / 1073741824.0);
}

float Noise::smoothNoise1D(int x) {
	return noise1D(x)/2 + noise1D(x-1)/4 + noise1D(x+1)/4; 
}

float Noise::smoothNoise2D(int x, int y) {
	float a = (noise2D(x-1, y-1) + noise2D(x+1, y-1) + noise2D(x-1, y+1) + noise2D(x+1, y+1) ) / 16;
    float b = (noise2D(x-1, y  ) + noise2D(x+1, y  ) + noise2D(x  , y-1) + noise2D(x  , y+1) ) /  8;
    float c = (noise2D(x  , y  ) / 4);
    
    return (a + b + c);
}

float Noise::smoothNoise3D(int x, int y, int z) {
	return 0.0;
}
    	
float Noise::interpolatedNoise1D(float x) {
	int   int_x   = (int)x;
	float fract_x = x - int_x;
	
	float v1 = smoothNoise1D(int_x);
	float v2 = smoothNoise1D(int_x + 1);
	
	return cosineInterpolator(v1, v2, fract_x);
}

float Noise::interpolatedNoise2D(float x, float y) {
	int   int_x  = (int)x;
	float fract_x = x - int_x;
	
	int   int_y   = (int) y;
	float fract_y = y - int_y;

	float v1 = smoothNoise2D(int_x,     int_y    );
	float v2 = smoothNoise2D(int_x + 1, int_y    );
	float v3 = smoothNoise2D(int_x,     int_y + 1);
	float v4 = smoothNoise2D(int_x + 1, int_y + 1);

	float i1 = cosineInterpolator(v1, v2 ,fract_x);
	float i2 = cosineInterpolator(v3, v4 ,fract_x);

	return cosineInterpolator(i1 ,i2 ,fract_y);
}

float Noise::interpolatedNoise3D(float x, float y, float z) {
	float total = 0.0;
	return total;
}

float Noise::perlinNoise1D(float x, float ifreq, float persistence, int octaves) {
	float total = 0;
	int   n     = octaves - 1;
	float freq = ifreq, amp;
	
	for (int i = 0; i < n; i++) {
		//freq = powf(ifreq,i)
		//amp  = powf(persistence,i);
		freq = freq * 2;
		amp  = amp * persistence;		
		total += (interpolatedNoise1D(x*freq)*amp);
	}
	
	return total;
}

float Noise::perlinNoise2D(float x, float y, float ifreq, float persistence, int octaves) {
	float total = 0;
	int   n     = octaves - 1;
	float freq = ifreq, amp = 1.0;
	
	for (int i = 0; i < n; i++) {
		//freq = powf(ifreq,i)
		//amp  = powf(persistence,i);
		freq = freq * 2;
		amp  = amp * persistence;		
		total += (interpolatedNoise2D(x*freq, y*freq)*amp);
	}
	 
	return total;
}

float Noise::perlinNoise3D(float x, float y, float z, float ifreq, float persistence, int octaves) {
	float total = 0;
	int   n     = octaves - 1;
	float freq = ifreq, amp;
	
	for (int i = 0; i < n; i++) {
		//freq = powf(ifreq,i)
		//amp  = powf(persistence,i);
		freq = freq * 2;
		amp  = amp * persistence;		
		total += (interpolatedNoise3D(x*freq, y*freq, z*freq)*amp);
	}
	 
	return total;
}