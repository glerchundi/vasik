#ifndef WINDOW_H__
#define WINDOW_H__

#include "TVasik.h"	

#include <GL/glfw.h>

class window : public TPlugin {
public:
	// construct & destruct
	window();
	~window();
	// plugin func's
	void    init(const char *title, int width, int height, int bpp, bool full);
	void    quit(void);
	
    int     setupview(int width, int height, bool ortho);
    int     clear(void);
    int     cleardepth(void);
    int     clearcolor(void);
    int     getwidth(void);
    int     getheight(void);
	int     swapbuffers(void);

	bool    isfinished(void);
	void    eventhandler(void);
	bool    getkeystate(int keysym);
private:
	// plugin var's
	int   w,h,bpp;
	int   view_w,view_h;
	bool  full,finished;
	bool  keys[512];
};

#endif
