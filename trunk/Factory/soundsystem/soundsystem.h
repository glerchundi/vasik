#ifndef SOUNDSYSTEM_H__
#define SOUNDSYSTEM_H__

#include "TVasik.h"

extern "C" {
    #include "fmod.h"
    #include "fmod_errors.h"
    #include "wincompat.h"
}

#include "FFT.h"

#define DEFAULT_SAMPLERATE     44100
#define DEFAULT_FFTSIZE        512
#define DEFAULT_SUBBANDS       32
#define DEFAULT_HISTORYSAMPLES 43
#define DEFAULT_THRESHOLD      150

#define DETECTBEAT_UNIFORM     0
#define DETECTBEAT_LINEAR      1
#define DETECTBEAT_EXPONENTIAL 2

class soundsystem {
public:
    // construct & destruct
    soundsystem();
    ~soundsystem();
    // plugin func's
    int     init(void);
    void    quit(void);    
    void    loadmodule(char *name, const char *path);
    void    loadstream(char *name, const char *path);
    void    playmodule(char *name);
    void    playstream(char *name);
    
    int     fftsize(void);
    void    fftsize(int size);
    void    spectrum(bool value);
	void window(int a);
    double* getspectrum(void);

    void    detection_subbands(int sbands);
	void    detection_historysamples(int hsamples);
	void    detection_threshold(int thold);
    void    detection_method(int method);
    void    detectbeat(char *name);    
private:
	void    detection_allocate(int subbands, int hsamples);
    // plugin var's
    int     samplerate;
    TList<FMUSIC_MODULE*> modules;
    TList<FSOUND_STREAM*> streams;
    // Spectrum
    FFT     fft;
    bool    spectrum_state;
    double  *fft_out,*fft_in;   
    // Beat Detection
    float   *Ei,*Es,*V;
	float   **Eh,LastMs;
	int     *EnergyBandsize,learning;
	int     historysamples,subbands,fft_size,fft_samplesize,oldpos,threshold;
};

#endif
