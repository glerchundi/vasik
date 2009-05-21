#ifndef GLWINDOW_H__
#define GLWINDOW_H__

/*
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
*/
		
#include "TVasik.h"	
#include <GL/glfw.h>

class glwindow
{
public:
	// construct & destruct
	glwindow();
	~glwindow();
	// plugin func's
	int  init(const char *title, int width, int height, int bpp, bool full);
	void quit(void);
	void setupgl(int width, int height);
	void swapbuffers(void);
	bool isfinished(void);
	void eventhandler(void);
	bool getkeystate(int keysym);
private:
	// plugin var's
	int   w,h,bpp;
	int   view_w,view_h;
	bool  full,finished;
	bool  keys[512];
};

#endif
