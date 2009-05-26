#ifndef TVASIK_H__
#define TVASIK_H__

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TLog.h"
#include "TList.h"
#include "TPlugin.h"

#ifdef __MACOSX__
	#include <OpenGL/CGLContext.h>
    #include <OpenGL/CGLCurrent.h>
    #include "OpenGL/gl.h"
    #include "OpenGL/glu.h"

    #include "CoreFoundation/CoreFoundation.h"

	// Needed by 'soundsystem' plugin
	#ifdef __MACH__
    	#include <Carbon/Carbon.h>
	#else
    	#include <Carbon.h>    /* For MPAllocateAligned() */
	#endif
#elif	__WIN32__
    #include <windows.h>
    #include "GL/gl.h"
    #include "GL/glu.h"
#elif   __LINUX__
    #include "GL/gl.h"
    #include "GL/glu.h"
#endif


#define DEBUG 1

#if defined(DEBUG)
    #define LOGTHIS(fmt, ...) TLog::log(__FILE__,__LINE__,fmt,__VA_ARGS__)
#else
    #define LOGTHIS(fmt, ...) 
#endif

typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

class TVasik {
	public:
		TVasik();
		TVasik(const char *name);
		~TVasik();
		void loadscript(const char *name);
	private:
        void changedir(void);
};

#endif
