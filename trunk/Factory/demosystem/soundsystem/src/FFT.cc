#include "FFT.h"

/* Reference: "Numerical Recipes in C" 2nd Ed.
 * by W.H.Press, S.A.Teukolsky, W.T.Vetterling, B.P.Flannery
 * (1992) Cambridge University Press.
 * ISBN 0-521-43108-5
 * Sec.13.4 - Data Windowing
 */
double
parzen (int i, int nn)
{
  return (1.0 - fabs (((double)i-0.5*(double)(nn-1))
		      /(0.5*(double)(nn+1))));
}

double
welch (int i, int nn)
{
  return (1.0-(((double)i-0.5*(double)(nn-1))
	       /(0.5*(double)(nn+1)))
	  *(((double)i-0.5*(double)(nn-1))
	    /(0.5*(double)(nn+1))));
}

double
hanning (int i, int nn)
{
  return ( 0.5 * (1.0 - cos (2.0*M_PI*(double)i/(double)(nn-1))) );
}

/* Reference: "Digital Filters and Signal Processing" 2nd Ed.
 * by L. B. Jackson. (1989) Kluwer Academic Publishers.
 * ISBN 0-89838-276-9
 * Sec.7.3 - Windows in Spectrum Analysis
 */
double
hamming (int i, int nn)
{
  return ( 0.54 - 0.46 * cos (2.0*M_PI*(double)i/(double)(nn-1)) );
}

double
blackman (int i, int nn)
{
  return ( 0.42 - 0.5 * cos (2.0*M_PI*(double)i/(double)(nn-1))
	  + 0.08 * cos (4.0*M_PI*(double)i/(double)(nn-1)) );
}

double
steeper (int i, int nn)
{
  return ( 0.375
	  - 0.5 * cos (2.0*M_PI*(double)i/(double)(nn-1))
	  + 0.125 * cos (4.0*M_PI*(double)i/(double)(nn-1)) );
}

FFT::FFT(void) {
	fft     = NULL;
	fftwout = NULL;
	window  = NULL;
	
	FFTsize(FFT_DEFAULTSIZE);
}

FFT::FFT(int size) {
	fft     = NULL;
	fftwout = NULL;
	window  = NULL;
	
	FFTsize(size);
}

FFT::~FFT(void) {
	if(fftwout) fftw_free(fftwout);
	if(fft)     delete [] fft;
}

void
FFT::FFTsize(int size) {
	if(!((size != 0) && !(size & (size - 1)))) {
		LOGTHIS("FFT size must be power of two (%i != 2^x)", size);
		return;
	}
	
	if(fftwout) fftw_free(fftwout);

	fft_size       = size;	
	fft_samplesize = fft_size*2;
	fftwout        = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*(fft_size+1));
	fft            = new double[fft_size];
}

void
FFT::FFTwindow(int window_id) {
	switch(window_id) {
		case  1: window = parzen;   break;
		case  2: window = welch;    break;
		case  3: window = hanning;  break;
		case  4: window = hamming;  break;
		case  5: window = blackman; break;
		case  6: window = steeper;  break;
		default:
		case  0: window = NULL;     break;		
	}
}

double*
FFT::FFTexecute(double *x, double scale) {
	int i,n;
	
	n = fft_samplesize;
	
	if(window) {
		for (i = 0; i < n; i ++) {
			x[i] = x[i] * window (i, n) * scale;
		}
    } else {
		for (i = 0; i < n; i ++) {
			x[i] = x[i] * scale;
		}    	
    }
	
	plan_forward = fftw_plan_dft_r2c_1d(n, x, fftwout, FFTW_ESTIMATE);
	fftw_execute(plan_forward);
	
	for(i = 0 ; i < fft_size ; i++) {
		fft[i] = sqrt(fftwout[i+1][0]*fftwout[i+1][0] +
		              fftwout[i+1][1]*fftwout[i+1][1]);
	}
	
	return fft;
}