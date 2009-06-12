#ifndef SHELL_H__
#define SHELL_H__

#include "TVasik.h"

#define SHELL_PREFIX "shell> "

class shell : public TPlugin {
public:
	// construct & destruct
	shell();
	~shell();
	// plugin func's
    void    initplugin(char *name, TPlugin *plugin);
	void    init(void);
    void    quit(void);
    // other wrapping func's
    int     onBottom(void);
    int     onTop(void);
    int     render(void);
private:
	// plugin var's
    param   vars[MAXPARAMS],*ret;
    int     windowWidth,windowHeight,timerId;
    int     currentMs,lastBlinkMs,lastErrorMs;
    int     xOffset,yOffset,yPosition;
    char    blinkCursor;
};

#endif
