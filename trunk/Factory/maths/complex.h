#ifndef COMPLEX_H__
#define COMPLEX_H__

#include <math.h>

class complex
{
public:
	complex();
	complex(float r, float i);
	double operator[](int index);
	double operator=(int index);	
private:
	double c[2];
};

#endif