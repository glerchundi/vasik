#include "font.h"

WRAPPLUGIN(font)
WRAPFUNC2(_int,setFont,_pchar,_int)
WRAPFUNC4(_int,setColor,_float,_float,_float,_float)
WRAPFUNC3(_int,drawText,_int,_int,_pchar)
WRAPFUNC0(_int,getHeight)
WRAPFUNC1(_int,getWidth,_pchar);

font::font() {
    SHAREPLUGIN(font);
    SHAREFUNC(setFont);
    SHAREFUNC(setColor);
    SHAREFUNC(drawText);
    SHAREFUNC(getHeight);
    SHAREFUNC(getWidth);

    color[0] = 
    color[1] = 
    color[2] = 
    color[3] = 1.0;

    fnt = NULL;
}

font::~font() {
}

void
font::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
font::init(void) {
}

void
font::quit(void) {
}

int
font::setFont(char *fontname, int size) {
    if(fnt != NULL) {
        delete fnt;
    }
    fnt = new glFont(fontname, size);
}

int
font::setColor(float r, float g, float b, float a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

int
font::drawText(int x, int y, char *fmt, ...) {
    va_list args;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(color[0],color[1],color[2],color[3]);
    
    va_start(args, fmt);
    vsnprintf(text, sizeof(text), fmt, args);
    fnt->drawText(x,y,"%s",text);
    va_end(args);
}

int
font::getHeight(void) {
    return fnt->getHeight();
}

int
font::getWidth(char *fmt, ...) {
    int ret;
    va_list args;

    va_start(args, fmt);
    vsnprintf(text, sizeof(text), fmt, args);
    ret = fnt->calcStringWidth(text);
    va_end(args);

    return ret; 
}
