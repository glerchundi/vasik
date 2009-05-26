#ifndef GLWINDOW_H__
#define GLWINDOW_H__

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
