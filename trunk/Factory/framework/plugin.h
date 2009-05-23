#ifndef PLUGIN_H__
#define PLUGIN_H__

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

#include "TVasik.h"

class plugin
{
public:
	// construct & destruct
	plugin();
	~plugin();
	// plugin func's
	void  init(void);
	void  quit(void);
	// other wrapping func's
	// ...
private:
	// plugin var's
	// ...
};

#endif

