#ifndef WINDOW_H__
#define WINDOW_H__

#include "TVasik.h"	

#define GLFW_DLL
extern "C" {
    #include <GL/glfw.h>
}

class window : public TPlugin {
public:
	// construct & destruct
	window();
	~window();
	// plugin func's
    void    initplugin(char *name, TPlugin *plugin);
	void    init(const char *title, int width, int height, int bpp, bool full);
	void    quit(void);
	
    int     setupview(int width, int height, bool ortho);
    int     clear(void);
    int     cleardepth(void);
    int     clearcolor(void);
    int     getwidth(void);
    int     getheight(void);
    int     addkeyboardcallback(void *);
	int     swapbuffers(void);

	bool    isfinished(void);
private:
	// plugin var's
	int     w,h,bpp;
	int     view_w,view_h;
	bool    full,finished;
};

#endif
