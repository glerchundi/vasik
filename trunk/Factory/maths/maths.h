#ifndef _MATHS_H_
#define _MATHS_H_

#define PI    3.14159265358
#define TWOPI 6.28318530718

#include "dsp.h"

class maths
{
public:
	void test(void);
	double* fft(double *data, int N);
};

#endif