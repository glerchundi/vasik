#ifndef TSCRIPT_H__
#define TSCRIPT_H__

#ifdef __WIN32__
    #ifdef EXPORTAPI
        #define VASIKAPI __declspec(dllexport)    
    #else
        #define VASIKAPI __declspec(dllimport)
    #endif    
#else
    #define VASIKAPI
#endif

#ifdef __MACOSX__
    #include "CoreFoundation/CoreFoundation.h"
	#include <unistd.h>
#elif	__WIN32__
    #include <windows.h>
    #include <cstdio>
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "TLog.h"
#include "TFunctionDefines.h"

class VASIKAPI TScript {
public:
    static lua_State *state;

    static void dumpstack(void);
    static void load(const char *name);
    static void dostring(const char *cmd, char *error);
private:
    static void changedir(void);
};

#endif
