#ifndef TLOG_H__
#define TLOG_H__

#include <stdio.h>
#include <stdarg.h>

#define DEBUG 1

#ifdef DEBUG
    #define LOGTHIS(fmt, ...) TLog::log(__FILE__,__LINE__,fmt,__VA_ARGS__)
#else
    #define LOGTHIS(fmt, ...) 
#endif

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class TLog
{
public:
	static void log(const char *file, const int line, const char *fmt, ...);
private:
    static int nargs(const char *fmt);
    static int validatechar(const char *fmt, int i);
};

#endif
