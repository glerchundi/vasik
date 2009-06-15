#include "dsp.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

dsp::dsp()
{
}

#define WGN 1000
/*
double x [] = {
   2.035504,-0.248280,-0.077388,0.999913,-0.354862,0.218934,0.696745,-0.495171,1.167828,-1.499104,1.237557,
  -0.871304,-1.297614,0.551944,0.097819,0.427420,-0.828003,-1.257537,1.008400,-1.408217,0.821650,2.134247,
  -1.766933,1.714084,1.231262,0.388487,-0.879513,1.620322,-1.318958,-1.220350,-1.326769,-0.625245,-0.540411,
  -0.900357,0.493306,-0.029633,0.723013,-1.950381,-0.187037,-0.562146,0.623944,-0.241075,-0.154250,0.410169,
   0.114029,1.411549,1.230693,-1.449264,0.508021,-0.107139,1.970981,-0.830574,-0.465383,-0.226968,1.073422,
  -0.697093,0.496055,0.573236,-1.056005,-2.116637,1.151586,0.373253,-0.887771,0.144863,0.148408,-1.007132
};
*/

void dsp::test(int N, float fcos, float f,float d)
{
	double *ret;
	double *x;
	x = new double[WGN];
	
	//puts("coseno");
	//printf("[");
	for(int i = 0 ; i < WGN ; i++) {
		x[i] = cos(2*3.1415926*fcos*i/(float)WGN);
		//printf("%f ",x[i]);
	}
	//printf("]");
	
	ret = welch((double *)x,WGN,f,d);
	
	printf("[");
	for(int i = 0 ; i < 512 ; i++)
		printf("%f ",ret[i]);
	printf("]");
	
	delete x;
}

//
// Welch Spectrum Estimation
// N = (K-1)*D + M
// Sx(w) = (1/K)*SUM(k=0,K-1,(1/Ev)*SUM(n=0,M-1,x(n)*v(n)*exp(-jwn)))
//
double* dsp::welch(double *x, int N, float fs = 1.0, float d = 0.5)
{
	int     i,n,k,M,K,s,e,tmpi;
	float   Ev;
	double  *v,*c,*ret,tmpd,w,f;
	
        M  = (int)sqrt((double)N);
	K  = (int)(((float)M - d)/(1.0-d));

	Ev  = 0.0;
	v   = new double[M];
	c   = new double[2];
	ret = new double[512];
	s   = -(int)(M/2.0);
	e   = ((M % 2) == 0) ? -s-1 : -s;
	
	// create overlaping window
	for(i = s; i <= e ; i++)
	{
		// hanning window v(i) = 0.5 + 0.5*cos(2*PI*i/N)
		// hamming window v(i) = 0.54 + 0.46*cos(2*PI*i/N)				
		v[i-s] = 0.5 + 0.5*cos(2*3.1415926*i/(float)M);
		// calc window energy
		Ev += v[i-s]*v[i-s];
	}
	
	for(i = 0 ; i < 512 ; i++)
	{
		f = (fs/2.0)*(i/512.0);
		w = 3.1415926*i/512.0;
		// calc segments average
		ret[i] = 0.0;
		//printf("PULSACION: %f\n",w);
		for(k = 0 ; k < K ; k++)
		{
			// calc periodogram of n segment
			tmpi = k*(int)((1-d)*M);
			c[0] = c[1] = 0.0;
			for(n = 0 ; n < M ; n++)
			{
				s    = n+tmpi;
				tmpd = x[s]*v[n];
				c[0] = c[0] + tmpd*cos(w*n);
				c[1] = c[1] + tmpd*sin(w*n);
			}
			ret[i] += (1.0/Ev)*(sqrt(c[0]*c[0] + c[1]*c[1]));
		}
		ret[i] /= (double)K;
		//printf("%f ",ret[i]);
	}
	
	delete v,c;
	
	return ret;
}

/*
for(i = 0 ; i < M ; i++)
	printf("v[%i] = %f\n",i,v[i]);
printf("Window Energy: %f\n",Ev);
printf("N = (K-1)*(1-d)*M + M\n");
printf("%i = (%i-1)*(1-%f)*%i + %i\n",N,K,d,M,M);
printf("%i = %i\n",N,(int)((K-1)*(1-d)*M + M));

	require('maths');
	m = maths:maths();
	d = maths.dsp();
	d:test(55,11015,44100,0.5);
*/
