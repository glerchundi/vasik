#ifndef TSCRIPT_H__
#define TSCRIPT_H__

#include <unistd.h>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#ifdef __MACOSX__
    #include "CoreFoundation/CoreFoundation.h"
#endif

#include "TLog.h"

class TScript {
public:
	static lua_State *state;

    static void dumpstack(void);
    static void load(const char *name);
private:
    static void changedir(void);
};

#endif
