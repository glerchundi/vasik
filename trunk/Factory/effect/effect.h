#ifndef EFFECT_H__
#define EFFECT_H__

#ifdef  __APPLE__
	#include <OpenGL/CGLContext.h>
	#include <OpenGL/CGLCurrent.h>	
	#include "OpenGL/gl.h"
	#include "OpenGL/glu.h"
#elif   __WIN32__
	#include <windows.h>
	#include "GL/gl.h"
	#include "GL/glu.h"
#elif   __LINUX__
	#include "GL/gl.h"
	#include "GL/glu.h"
#endif

#include <stdlib.h>

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

