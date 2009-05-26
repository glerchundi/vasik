#ifndef PLUGIN_H__
#define PLUGIN_H__

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

