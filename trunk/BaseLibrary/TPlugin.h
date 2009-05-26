#ifndef TPLUGIN_H__
#define TPLUGIN_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1024

class TPlugin {
public:
	TPlugin();
	TPlugin(char *plugin);
	~TPlugin();
	
	void  LinkPlugin(char *plugin);
	void* ExecuteFunction(char *func, ...);
private:
	bool linked;
	char pluginname[MAXCHAR];
	char string[MAXCHAR];
};

#endif
