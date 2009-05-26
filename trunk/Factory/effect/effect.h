#ifndef EFFECT_H__
#define EFFECT_H__

#include "TVasik.h"

class effect
{
public:
	// construct & destruct
	effect();
	~effect();
	// plugin func's
	void init(void);
    void quit(void);
	void render(void);
    void render(double* data);
    void print(void);
private:
	// plugin var's
};

#endif

