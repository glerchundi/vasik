#include "shell.h"

#define BUFSIZE 64

static TList<char*> cmdHistory;

static char output[BUFSIZE];
static char buffer[BUFSIZE];
static char current[BUFSIZE];
static char errorStr[BUFSIZE];

static int bufferCnt, cmdPos;

static int
onKey(int key, int keystate) {
    if(keystate) {
        char cKey = (char)key;
        if(key < 256) {
            buffer[bufferCnt]   = (char)key;
            buffer[bufferCnt+1] = '\0';
            bufferCnt++;
        }
        switch(key) {
            case 283: // UP
                if(cmdPos == cmdHistory.size()) {
                    snprintf(current,bufferCnt+1,"%s",buffer);
                }
                if(cmdPos) {
                    char *s = cmdHistory.get(--cmdPos);
                    snprintf(buffer,BUFSIZE,"%s",s);
                    bufferCnt = strlen(s);
                }
                break;
            case 284: // DOWN
                if(cmdPos == cmdHistory.size()-1) {
                    memset(buffer,' ',BUFSIZE);
                    snprintf(buffer,BUFSIZE,"%s",current);
                    bufferCnt = strlen(current);
                    cmdPos++;
                }
                if(cmdPos < cmdHistory.size()-1) {
                    char *s = cmdHistory.get(++cmdPos);
                    snprintf(buffer,BUFSIZE,"%s",s);
                    bufferCnt = strlen(s);
                }
                break;
            case 285: // LEFT
                break;
            case 286: // RIGHT
                break;
            case 294: // ENTER
                if(bufferCnt) {
                    // save string in history
                    char *s = new char[bufferCnt+1];
                    snprintf(s,bufferCnt+1,"%s",buffer);
                    cmdHistory.add(NULL, s);
                    cmdPos = cmdHistory.size();
                    // execute string in the script
                    TScript::dostring(buffer,errorStr);
                    memset(buffer,' ', BUFSIZE);
                    buffer[0] = '\0';
                    bufferCnt = 0;
                }
                break;
            case 295: // BACKWARD
                if(bufferCnt) {
                    buffer[--bufferCnt] = '\0';
                }
                break;
            default:
                break;
        }
    }

    return 0;
}

WRAPPLUGIN(shell)
WRAPFUNC0(_int,render)

shell::shell() {
    SHAREPLUGIN(shell);
    SHAREFUNC(render);
}

shell::~shell() {
}

void
shell::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
shell::init(void) {
    cmdPos      = 0;
    bufferCnt   = 0;
    currentMs   = 0;
    lastBlinkMs = 0;
    lastErrorMs = 0;
    xOffset     = 0;
    yOffset     = 0;
    yPosition   = 0;
    blinkCursor = ' ';

    vars[0]._pvoid = (void *)&onKey;
    execute("window","addkeyboardcallback",vars);   
    
    ret = execute("window","getwidth",NULL);
    windowWidth = ret->_int;
    ret = execute("window","getheight",NULL);
    windowHeight = ret->_int;
    ret = execute("timer","createTimer",NULL);
    timerId = ret->_int;

    vars[0]._int = timerId;
    execute("timer","start",vars);
    vars[0]._pchar = SHELL_PREFIX;
    ret = execute("font","getWidth",vars);
    xOffset = ret->_int;
    ret = execute("font","getHeight",NULL);
    yOffset = ret->_int;

    onBottom();
}

void
shell::quit(void) {
}

int
shell::onTop(void) {
    yPosition = 0;

    return 0;
}

int
shell::onBottom(void) {
    yPosition = windowHeight - yOffset;

    return 0;
}

int
shell::render(void) {
    vars[0]._int    = timerId;
    ret = execute("timer","getMs",vars);
    currentMs = ret->_int;

    vars[0]._int    = windowWidth;
    vars[1]._int    = windowHeight;
    vars[2]._bool   = true;
    execute("window","setupview",vars);

    // Shell commands
    
    vars[0]._int    = 0;
    vars[1]._int    = yPosition;
    vars[2]._pchar  = SHELL_PREFIX;
    execute("font","drawText",vars);

    if(currentMs-lastBlinkMs > 500) {
        lastBlinkMs = currentMs;
        blinkCursor = (blinkCursor == ' ') ? '_' : ' ';
    }

    snprintf(output,BUFSIZE,"%s%c",buffer,blinkCursor);

    vars[0]._int    = xOffset;
    vars[1]._int    = yPosition;
    vars[2]._pchar  = output;
    execute("font","drawText",vars);

    // Error messages
    vars[0]._int    = 0;
    vars[1]._int    = 0;
    vars[2]._pchar  = errorStr;
    execute("font","drawText",vars);

    return 0;
}
