#ifndef EFFECT_H__
#define EFFECT_H__

#include "TVasik.h"

class effect : public TPlugin
{
public:
	// construct & destruct
	effect();
	~effect();
	// plugin func's
	void 		init(void);
    void        initplugin(char *name, TPlugin *plugin);
    void 		quit(void);

	int	 		render(void);
    int         setup(void);
private:
	// plugin var's
    param   vars[MAXPARAMS],*ret;
    int     windowWidth,windowHeight,timerId,ms;
    bool    _setup;
};

#endif
