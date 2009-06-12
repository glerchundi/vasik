#include "soundsystem.h"

// TODO
// ** calc a,b for different FFT sizes 256,512,1024,2048,4096,8192
// ** real-time subbands, historysamples changing method critical section implementation
// ** calculate fft using fftw

// EnergyBandsize[i] = a*i + b   [1..ENERGY_SUBBANDS]
// EQ1: a + b = 1
// EQ2: n*b + a*n*((n+1)/2) = FFT_BUFFERSIZE 
float linear[24] = {
	2  , 510.0000000 , -509.0000000 ,
	4  , 84.66666667 , -83.66666667 ,
	8  , 18.00000000 , -17.00000000 ,
	16 , 4.133333333 , -3.133333333 ,
	32 , 0.967741935 ,  0.032258064 ,
	64 , 0.222222222 ,  0.777777777 ,
	128, 0.047244094 ,  0.952755905 ,
	256, 0.007843137 ,  0.992156862 ,
};
// EnergyBandsize[i] = a*exp(-x*b) [1..ENERGY_SUBBANDS]
// EQ1: a*exp(-b) = 1
// EQ2: sum(1,n,a*exp(-x*b)) = FFT_BUFFERSIZE
float exponential[24] = {
	2  , 0.001956947 ,  6.236369590 ,
	4  , 0.130975500 ,  2.032744996 ,
	8  , 0.446197884 ,  0.806992738 ,
	16 , 0.717530980 ,  0.331939153 ,
	32 , 0.873805299 ,  0.134897697 ,
	64 , 0.948994414 ,  0.052352365 ,
	128, 0.981806636 ,  0.018360897 ,
	256, 0.995088192 ,  0.004923916 ,
};

soundsystem::soundsystem(void) {
	learning         = 0;
	LastMs	         = 0;
		
	Eh               = NULL;
	EnergyBandsize   = NULL;
	Ei = Es = V      = NULL;
	fft_in = fft_out = NULL;
	
	samplerate       = DEFAULT_SAMPLERATE;
	subbands         = DEFAULT_SUBBANDS;
	historysamples   = DEFAULT_HISTORYSAMPLES;
	threshold        = DEFAULT_THRESHOLD;
	fftsize(DEFAULT_FFTSIZE);
	
	spectrum_state   = false;

	detection_allocate(subbands, historysamples);
	detection_method(DETECTBEAT_EXPONENTIAL);
}

soundsystem::~soundsystem() {
}

void
soundsystem::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
soundsystem::init(void) {
    if (!FSOUND_Init(samplerate, 32, FSOUND_INIT_USEDEFAULTMIDISYNTH)) {
        LOGTHIS("%s\n", FMOD_ErrorString(FSOUND_GetError()));
    }
}

void
soundsystem::quit(void) {
	int i;
	for(i = 0 ; i < modules.size() ; i++)
		FMUSIC_FreeSong(modules.get(i));
	for(i = 0 ; i < streams.size() ; i++)
		FSOUND_Stream_Close(streams.get(i));
		
	FSOUND_Close();
}

void
soundsystem::loadmodule(char *name, const char *path) {
    modules.add(name,FMUSIC_LoadSong(path));
}

void
soundsystem::loadstream(char *name, const char *path) {
    streams.add(name,FSOUND_Stream_Open(path,FSOUND_NORMAL|FSOUND_MPEGACCURATE,0,0));
}

void
soundsystem::playmodule(char *name) {
    FMUSIC_PlaySong(modules.get(name));
}

void
soundsystem::playstream(char *name) {
	FSOUND_Stream_Play(0,streams.get(name));
}

int
soundsystem::fftsize(void) {
	return fft_size;
}

void
soundsystem::fftsize(int size) {
	fft_size       = size;
	fft_samplesize = fft_size*2;
	
	fft.FFTsize(fft_size);
	
	if(fft_in) delete [] fft_in;
	
	fft_in = new double[fft_samplesize];
}

void
soundsystem::spectrum(bool value) {
    spectrum_state = value;
    FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), spectrum_state);
}

void
soundsystem::window(int a) {
	fft.FFTwindow(a);
}

double*
soundsystem::getspectrum(void) {
	void         *p1,*p2;
	unsigned int blen1,blen2,actpos;
	int          i,*pi1,*pi2;
	
	FSOUND_SAMPLE *sample = FSOUND_GetCurrentSample(0);
	// 0 - 34816
	actpos = FSOUND_GetCurrentPosition (0);
	if(oldpos != actpos) {

		FSOUND_Sample_Lock (sample,oldpos*4,1024*4,&p1,&p2,&blen1,&blen2);
		pi1 = (int *)p1;
		pi2 = (int *)p2;
		
		// Mix left and right channel
		for(i = 0 ; i < fft_samplesize ; i++) {
			fft_in[i] = (((pi1[i] >> 16) & 0x0000FFFF) + (pi1[i] & 0x0000FFFF))/2.0;
		}
		
		fft_out = fft.FFTexecute(fft_in, 1.0);
		
		FSOUND_Sample_Unlock(sample,p1,p2,blen1,blen2);
		oldpos = actpos;
	}
	return fft_out;
}

/*
// FMOD based FFT
double* soundsystem::getspectrum(void) {
	double *a = (double *)FSOUND_DSP_GetSpectrum();
	return ((spectrum_state) ? a : NULL);
}
*/


void
soundsystem::detection_allocate(int sbands, int hsamples) {
	int i;
	
	// free
	if(Eh) {
		for(i = 0 ; i < subbands ; i++) {
			if(Eh[i]) delete [] Eh[i];
		}
		delete [] Eh;
	}
	if(EnergyBandsize) delete [] EnergyBandsize;
	if(Ei)             delete [] Ei;
	if(Es)             delete [] Es;
	if(V)              delete [] V;
	
	// allocate
	Eh = new float*[sbands];
	for(i = 0 ; i < sbands ; i++) {
		Eh[i] = new float[hsamples];
	}

	EnergyBandsize = new int[sbands];
	Ei             = new float[sbands];
	Es             = new float[sbands];
	V              = new float[sbands];
	
	learning       = 0;
	subbands       = sbands;
	historysamples = hsamples;
}

void
soundsystem::detection_historysamples(int hsamples) {
	if(hsamples <= 0) {
		LOGTHIS("Number of energy history samples must be greater than 0 (%i <= 0)", hsamples);
		return;
	}
	detection_allocate(subbands, hsamples);
}

void
soundsystem::detection_subbands(int sbands) {
	if(!((sbands != 0) && !(sbands & (sbands - 1)))) {
		LOGTHIS("Number of subbands must be power of two (%i != 2^x)",sbands);
		return;
	}
	if(sbands >= fft_size) {
		LOGTHIS("Number of subbands must be less than FFT size (%i >= %i)",sbands,fft_size);
		return;
	}
	detection_allocate(sbands, historysamples);
}

void
soundsystem::detection_threshold(int thold) {
	threshold = thold;
}

void
soundsystem::detection_method(int method) {
	int i,sum;
	float a,b,df;
	float *values;	
	
	switch(method) {
		case DETECTBEAT_LINEAR:
			values = linear;
			break;
		case DETECTBEAT_EXPONENTIAL:
		default:
			values = exponential;		
			break;
	}
	
	for(i = 0 ; i < 8 ; i++) {
		if((int)values[i*3 + 0] == subbands) {
			a = values[i*3 + 1];
			b = values[i*3 + 2];
		}	
	}
	
	sum = 0;
	switch(method) {
		case DETECTBEAT_UNIFORM:
			for(i = 1 ; i <= subbands ; i++) {
				EnergyBandsize[i-1] = round(fft_size/(float)subbands);
				sum += EnergyBandsize[i-1];
			}
			break;
		case DETECTBEAT_LINEAR:
			for(i = 1 ; i <= subbands ; i++) {
				EnergyBandsize[i-1] = round(a*(float)i + b);
				sum += EnergyBandsize[i-1];
			}
			break;
		case DETECTBEAT_EXPONENTIAL:				
		default:
			for(i = 1 ; i <= subbands ; i++) {
				EnergyBandsize[i-1] = round(a*expf(b*(float)i));
				sum += EnergyBandsize[i-1];
			}
			break;
	}
	EnergyBandsize[subbands-1] += fft_size-sum;
}

void
soundsystem::detectbeat(char *name) {
	int     i,j,k,la,lb;
	double *B,CurrentMs;
	
	memset(Ei,0,subbands*sizeof(float));
	memset(Es,0,subbands*sizeof(float));
	memset(V ,0,subbands*sizeof(float));
	
	CurrentMs = FSOUND_Stream_GetTime(streams.get(name));
	if(CurrentMs-LastMs > 25) {
		B = this->getspectrum();
		for(i = 0 ; i < subbands ; i++) {
			la = 0; for(k = 0 ; k <= i-1 ; k++) la += EnergyBandsize[k];
			lb = 0; for(k = 0 ; k <= i   ; k++) lb += EnergyBandsize[k];
			for(j = la ; j < lb ; j++) {
				Es[i] += 10000*B[j];
			}
			Es[i] *= ((float)EnergyBandsize[i]/(float)fft_size);
		}
	
		// energy average for each subband
		for(i = 0 ; i < subbands ; i++) {
			for(j = 0 ; j < historysamples ; j++) {
				Ei[i] += Eh[i][j];
			}
			Ei[i] *= (1.0/historysamples);
		}
		// variance for each subband
		for(i = 0 ; i < subbands ; i++) {
			for(j = 0 ; j < historysamples ; j++) {
				V[i] += powf(Eh[i][j]-Ei[i],2);
			}
			V[i] *= (1.0/historysamples);
		}
		// right switch all buffer and save last instantaneous energy value
		for(i = 0 ; i < subbands ; i++) {
			for(j = historysamples-1 ; j > 0 ; j--) {
				Eh[i][j] = Eh[i][j-1];
			}
			Eh[i][0] = Es[i];
		}
		
		if(learning < historysamples) {
			learning++;
		} else {
			for(i = 0 ; i < subbands ; i++) {
				if(V[i] > threshold) 
					printf("[%2i] : BEAT! (V[%2i]=%6f V0=%6i)\n",i,i,V[i],threshold);
			}
		}
		LastMs = CurrentMs;
	}
}
