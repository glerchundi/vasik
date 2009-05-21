#ifndef TLOG_H__
#define TLOG_H__

#include <stdio.h>
#include <stdarg.h>

class TLog
{
public:
	static void log(const char *file, const int line, const char *fmt, ...);
private:
    static int nargs(const char *fmt);
    static int validatechar(const char *fmt, int i);
};

#endif
