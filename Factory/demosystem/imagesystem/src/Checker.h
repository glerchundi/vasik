#ifndef CHECKER_H__
#define CHECKER_H__

#include "FreeImage.h"

class Checker
{
public:
	static void doit(FIBITMAP *bitmap, int repeatx, int repeaty);
};

#endif
