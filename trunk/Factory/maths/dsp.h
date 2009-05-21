#ifndef DSP_H__
#define DSP_H__

#include <math.h>

class dsp
{
public:
	dsp();
	void test(int N, float fcos, float f, float d);
	double* welch(double *x, int N, float fs, float d);
private:
};

#endif