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
#ifndef __WIN32__
    #include <unistd.h>
#endif

#include "TLog.h"
#include "TList.h"
#include "TScript.h"
#include "TPlugin.h"

#include "TFunctionDefines.h"

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
    #define NOMINMAX
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <cstdio>
#elif   __LINUX__
    #include "GL/gl.h"
    #include "GL/glu.h"
#endif

typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

#endif
