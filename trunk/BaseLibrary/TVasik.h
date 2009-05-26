#ifndef TVASIK_H__
#define TVASIK_H__

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <time.h>

#include "TLog.h"
#include "TList.h"
#include "TPlugin.h"

#ifdef __APPLE__
    #include "CoreFoundation/CoreFoundation.h"
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
