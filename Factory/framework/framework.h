#ifndef FRAMEWORK_H__
#define FRAMEWORK_H__

#include "TVasik.h"

class framework : public TPlugin {
public:
	// construct & destruct
	framework();
	~framework();
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

