#include "window.h"

typedef int (ptKeyboardFunc)(int, int);
TList<ptKeyboardFunc*>* keyboardCallbacks;

WRAPPLUGIN(window)
WRAPFUNC3(_int,setupview,_int,_int,_bool)
WRAPFUNC0(_int,clear)
WRAPFUNC0(_int,cleardepth)
WRAPFUNC0(_int,clearcolor)
WRAPFUNC0(_int,getwidth)
WRAPFUNC0(_int,getheight)
WRAPFUNC1(_int,addkeyboardcallback,_pvoid)
WRAPFUNC0(_bool,isfinished)
WRAPFUNC0(_int,swapbuffers)

window::window(void) {
    SHAREPLUGIN(window);
    SHAREFUNC(setupview);
    SHAREFUNC(clear);
    SHAREFUNC(cleardepth);
    SHAREFUNC(clearcolor);
    SHAREFUNC(getwidth);
    SHAREFUNC(getheight);
    SHAREFUNC(addkeyboardcallback);
    SHAREFUNC(isfinished);
    SHAREFUNC(swapbuffers);

    keyboardCallbacks = new TList<ptKeyboardFunc*>();
	
    this->finished = false;
}

window::~window() {
}

void GLFWCALL
WindowSizeFun(int w, int h) {
}

void GLFWCALL
WindowRefreshFun(void) {
}

void GLFWCALL
MousePosFun(int x, int y) {
}

void GLFWCALL
MouseButtonFun(int button, int action) {
}

void
KeyboardFun(bool isKey, int key, int keystate) {
    bool doCallback = false;
    int i, s = keyboardCallbacks->size();

    if(isKey  && key > 255) doCallback = true;
    if(!isKey && key < 256) doCallback = true;

    if(doCallback) {
        for(i = 0 ; i < s ; i++) {
            ptKeyboardFunc *pt = keyboardCallbacks->get(i);
            pt(key, keystate);
        }
    }
}

void GLFWCALL
KeyboardKeyFun(int key, int keystate) {
    KeyboardFun(true, key,keystate);
}

void GLFWCALL
KeyboardCharFun(int key, int keystate) {
    KeyboardFun(false, key,keystate);
}

void
window::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void
window::init(const char *title, int width, int height, int bpp, bool full) {
    this->w         = width;
    this->h         = height;
    this->bpp       = bpp;
    this->full      = full;
    this->view_w    = this->w;
    this->view_h    = this->h;

	LOGTHIS("Opening window: w=%i h=%i bpp=%i full=%i",this->w,this->h,this->bpp,this->full);

    // Initialise GLFW
    glfwInit();

	int mode = (this->full) ? GLFW_FULLSCREEN : GLFW_WINDOW;

    // Open OpenGL window
    if(!glfwOpenWindow(this->w, this->h, 0,0,0,0, this->bpp, 0, mode)) {
        glfwTerminate();
    }

    // Set window title
    glfwSetWindowTitle(title);
    // Enable sticky,repeated and special keys
    glfwEnable(GLFW_STICKY_KEYS);
    //glfwEnable(GLFW_KEY_REPEAT);
    glfwEnable(GLFW_SYSTEM_KEYS);
    // Enable mouse cursor (only needed for fullscreen mode)
    glfwEnable(GLFW_MOUSE_CURSOR);
    // Disable automatic event polling
    //glfwDisable(GLFW_AUTO_POLL_EVENTS);

    // Set callback functions
    glfwSetWindowSizeCallback(WindowSizeFun);
    glfwSetWindowRefreshCallback(WindowRefreshFun);
    glfwSetMousePosCallback(MousePosFun);
    glfwSetMouseButtonCallback(MouseButtonFun);
    glfwSetKeyCallback(KeyboardKeyFun);
    glfwSetCharCallback(KeyboardCharFun);
   
    this->setupview(this->w,this->h, false);
}

void
window::quit(void) {
	LOGTHIS("%s","Closing window...");
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
	LOGTHIS("%s","Window closed");
}

int
window::setupview(int width, int height, bool ortho) {
	// height / width ration 
    float ratio;
    
    // protect against a divide by zero
	if(height == 0) {
		height = 1;
    }
    
    // setup our viewport.
    glViewport(0,0,width,height);
    
    // change to the projection matrix and set our viewing volume.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(ortho) {
        // set our orthographic view
        glOrtho(0.0f,width,height,0.0f,-1.0f,1.0f);
    }
    else {
        ratio = (float)width/(float)height;
        // set our perspective view
        gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return 0;
}

int
window::clear(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    return 0;
}

int
window::cleardepth(void) {
    glClear(GL_DEPTH_BUFFER_BIT);

    return 0;
}

int
window::clearcolor(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

int
window::getwidth(void) {
    return this->w;
}

int
window::getheight(void) {
    return this->h;
}

int
window::addkeyboardcallback(void *function) {
    ptKeyboardFunc *pt = (ptKeyboardFunc *)function;
    keyboardCallbacks->add(NULL, pt);

    return 0;
}

int
window::swapbuffers(void) {
    glfwSwapBuffers();

    return 0;
}

bool
window::isfinished(void) {
    return glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}
