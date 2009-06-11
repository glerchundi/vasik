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
#include <stdarg.h>

#include "TLog.h"
#include "TList.h"
#include "TScript.h"
#include "TPlugin.h"

#ifdef __MACOSX__
	#include <OpenGL/CGLContext.h>
    #include <OpenGL/CGLCurrent.h>
    #include "OpenGL/gl.h"
    #include "OpenGL/glu.h"

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

typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

#endif
