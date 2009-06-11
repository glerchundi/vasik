#include "complex.h"

complex::complex()
{
	c[0] = c[1] = 0.0;
}

complex::complex(float r, float i)
{
	c[0] = r;
	c[1] = i;
}

double complex::operator=(int index)
{
	return c[index];
}