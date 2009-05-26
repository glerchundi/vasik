#ifndef FFT_H__
#define FFT_H__

#include "TVasik.h"

extern "C" {
	#include "fftw3.h"
}

#define FFT_WINDOW_UNIFORM	0
#define FFT_WINDOW_PARZEN	1
#define FFT_WINDOW_WELCH	2
#define FFT_WINDOW_HANNING	3
#define FFT_WINDOW_HAMMING	4
#define FFT_WINDOW_BLACKMAN	5
#define FFT_WINDOW_STEEPER	6	

#define FFT_DEFAULTSIZE 	512

class FFT {
public:
    // construct & destruct
    FFT();
    FFT(int size);
    ~FFT();
    // funcs
    void    FFTsize(int size);
    void    FFTwindow(int window_id);
    double* FFTexecute(double *x, double scale);
private:
    // plugin var's
    double 			(*window)(int i, int nn);
    int     		fft_size,fft_samplesize;
	double* 		fft;
	
	fftw_complex 	*fftwout;
	fftw_plan 		plan_forward;
};

#endif
