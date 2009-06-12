#ifndef SCHEDULER_H__
#define SCHEDULER_H__

#include "TVasik.h"

class FuncKey {
public:
    FuncKey(void)   {};
    ~FuncKey(void)  {};

    int     t1;
    int     t2;
    char*   plugin;
    char*   func;
    bool    exec;
    param*  vars;
};

class scheduler : public TPlugin {
public:
	// construct & destruct
	scheduler();
	~scheduler();
	// plugin func's
    void    initplugin(char *name, TPlugin *plugin);
    void    init(int layers);
	void    quit(void);

    int     addfx(int layer, int t1, int t2, char *plugin, char *func, param *vars = NULL);
    int     play(int delayMs);
private:
	// plugin var's
	// ...
    param               p[MAXPARAMS];
    TList<TPlugin*>     plugins;
    TList<FuncKey*>     oneshot;
    TList<FuncKey*>*    layers;
    int                 nlayers;
};

#endif

