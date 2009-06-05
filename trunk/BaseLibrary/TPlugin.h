#ifndef TPLUGIN_H__
#define TPLUGIN_H__

#include "TLog.h"
#include "TScript.h"
#include "TList.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

union param
{
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
};

#define WRAPFUNC0(r,func)     				\
param* wrap_##func (param* params) {		\
	param* p=(param*)malloc(sizeof(param)); \
	p->r=sharedplugin->func();				\
	return p;								\
}

#define WRAPFUNC1(r,func,p1)				\
param* wrap_##func (param* params) {     	\
    param* p=(param*)malloc(sizeof(param)); \
	p->r=sharedplugin->func	(				\
							params.p1		\
							);          	\
    return p;                         		\
}

#define WRAPFUNC2(r,func,p1,p2)				\
param* wrap_##func (param* params) {     	\
    param* p=(param*)malloc(sizeof(param)); \
    p->r=sharedplugin->func	(           	\
                        	params.p1   	\
                        	params.p2   	\
                        	);          	\
    return p;                         		\
}

#define WRAPFUNC3(r,func,p1,p2,p3)			\
param* wrap_##func (param* params) {   		\
    param* p=(param*)malloc(sizeof(param)); \
	p->r=sharedplugin->func	(           	\
                        	params.p1   	\
                        	params.p2   	\
                        	params.p3   	\
                        	);          	\
    return p;                         		\
}

#define WRAPFUNC4(r,func,p1,p2,p3,p4)		\
param* wrap_##func (param* params) {  		\
    param* p=(param*)malloc(sizeof(param)); \
    p->r=sharedplugin->func	(          		\
                        	params.p1   	\
                        	params.p2   	\
                        	params.p3   	\
                        	params.p4   	\
                        	);          	\
    return p;                         		\
}

#define WRAPFUNC5(r,func,p1,p2,p3,p4,p5)	\
param* wrap_##func (param* params) {		\
    param* p=(param*)malloc(sizeof(param)); \
	p->r=sharedplugin->func	(           	\
                        	params.p1   	\
                        	params.p2   	\
                        	params.p3   	\
                        	params.p4   	\
                        	params.p5   	\
                        	);          	\
    return  p;                       		\
}

#define WRAPPLUGIN(p)						\
p *sharedplugin;

#define SHAREFUNC(f)						\
sharedplugin->addfunc(#f,&wrap_##f)

#define SHAREPLUGIN(p) sharedplugin = this;	\

#define MAXCHAR 1024

typedef param* (*ptFunc)(param *);

class TPlugin {
public:
	TPlugin();
	~TPlugin();
	
	param* 		execute(char *func, param* params);
	void 		addfunc(char *func, ptFunc f);

	/*void addplugin(char *plugin, TPlugin* p);*/
	/*TPlugin* getplugin(char *plugin);*/

private:
	/*TList<TPlugin*> *plugins;*/
	TList<ptFunc>	*funcs;
	char			cmd[MAXCHAR];
	char			pluginname[MAXCHAR];
	char			plugindescr[MAXCHAR];
};

#endif
