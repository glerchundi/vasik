#ifndef FONT_H__
#define FONT_H__

#include "TVasik.h"

#include "glFont.h"

class font : public TPlugin {
public:
	// construct & destruct
	font();
	~font();
	// plugin func's
	void    init(void);
	void    quit(void);
	// other wrapping func's
	// ...
    int     setFont(char *fontname, int size);
    int     setColor(float r, float g, float b, float a);
    int     drawText(int x, int y, char *fmt, ...);
private:
	// plugin var's
	//
    char    text[1024];
    float   color[4];
    glFont* fnt;
};

#endif
