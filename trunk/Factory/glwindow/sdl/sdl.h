#ifndef SDL_H__
#define SDL_H__

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
		
#include "TInguma.h"	
#include "SDL/SDL.h"

class sdl
{
public:
	// construct & destruct
	sdl();
	~sdl();
	// plugin func's
	int	 init(const char *title, int width, int height, int bpp, bool full);
	void quit(void);
	void setupgl(int width, int height);
	void swapbuffers(void);
	bool isfinished(void);
	void eventhandler(void);
	bool getkeystate(int keysym);
private:
	// plugin var's
	const 	SDL_VideoInfo *info;
	int		w,h,bpp;
	int		view_w,view_h;
	bool	full,finished;
	bool	keys[512];
};

#endif

