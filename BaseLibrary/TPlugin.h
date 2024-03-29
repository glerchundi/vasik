#ifndef TPLUGIN_H__
#define TPLUGIN_H__

#ifdef __WIN32__
    #ifdef EXPORTAPI
        #define VASIKAPI __declspec(dllexport)    
    #else
        #define VASIKAPI __declspec(dllimport)
    #endif    
#else
    #define VASIKAPI
#endif

#include "TLog.h"
#include "TScript.h"
#include "TList.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

typedef union myparam param;

union myparam
{
    bool    _bool;
    bool*   _pbool;
    char    _char;
    char*   _pchar;
    short   _short;
    short*  _pshort;
    int     _int;
    int*    _pint;
    long    _long;
    long*   _plong;
    float   _float;
    float*  _pfloat;
    double  _double;
    double* _pdouble;
    void*   _pvoid;
};

#define WRAPFUNC0(r,func)                   \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func();                   \
    return sharedParam;                     \
}

#define WRAPFUNC1(r,func,p1)                \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func	(                   \
                        params[0].p1        \
                        );                  \
    return sharedParam;                     \
}

#define WRAPFUNC2(r,func,p1,p2)             \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func  (                   \
                        params[0].p1,       \
                        params[1].p2        \
                        );                  \
    return sharedParam;                     \
}

#define WRAPFUNC3(r,func,p1,p2,p3)          \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func  (                   \
                        params[0].p1,       \
                        params[1].p2,       \
                        params[2].p3        \
                        );                  \
    return sharedParam;                     \
}

#define WRAPFUNC4(r,func,p1,p2,p3,p4)       \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func  (                   \
                        params[0].p1,       \
                        params[1].p2,       \
                        params[2].p3,       \
                        params[3].p4        \
                        );                  \
    return sharedParam;                     \
}

#define WRAPFUNC5(r,func,p1,p2,p3,p4,p5)    \
static                                      \
param* wrap_##func (param* params) {        \
    sharedParam->r =                        \
    sharedPlugin->func  (                   \
                        params[0].p1,       \
                        params[1].p2,       \
                        params[2].p3,       \
                        params[3].p4,       \
                        params[4].p5        \
                        );                  \
    return  sharedParam;                    \
}

#define WRAPPLUGIN(p)                       \
static param *sharedParam;                  \
static p *sharedPlugin;

#define SHAREFUNC(f)                        \
sharedPlugin->addfunc(#f,&wrap_##f);

#define SHAREPLUGIN(p)                      \
sharedParam = (param*)malloc(sizeof(param));\
sharedPlugin = this;

#define PLUGINNAME(name)                    \
snprintf(pluginname, MAXCHARSIZE, "%s", name);

#define PLUGINDESCR(descr)                  \
snprintf(plugindescr, MAXCHARSIZE, "%s", descr);

#define MAXCHARSIZE 1024
#define MAXPARAMS   5

typedef param* (*ptFunc)(param *);

class VASIKAPI TPlugin {
public:
    TPlugin();
    ~TPlugin();

    param*              execute(char *plugin, char *func, param* vars);
    param*              execute(char *func, param* vars);
    void                addplugin(char *plugin, TPlugin *p);
    void                addfunc(char *func, ptFunc f);

    char                pluginname[MAXCHARSIZE];
    char                plugindescr[MAXCHARSIZE];
//private:
	TList<ptFunc>*      funcs;
        char                cmd[MAXCHARSIZE];
    // another plugins used by inherit plugin!
    TList<TPlugin*>*    plugins;
};

#endif
