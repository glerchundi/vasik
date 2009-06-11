#include "window.h"

WRAPPLUGIN(window)
WRAPFUNC3(_int,setupview,_int,_int,_bool)
WRAPFUNC0(_int,clear)
WRAPFUNC0(_int,cleardepth)
WRAPFUNC0(_int,clearcolor)
WRAPFUNC0(_int,getwidth)
WRAPFUNC0(_int,getheight)
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
    SHAREFUNC(isfinished);
    SHAREFUNC(swapbuffers);

	this->finished = false;
	memset(keys,0,512);
}

window::~window() {
}

//========================================================================
// WindowSizeFun() - Window size callback function
//========================================================================

void GLFWCALL
WindowSizeFun(int w, int h) {
}

//========================================================================
// WindowRefreshFun() - Window refresh callback function
//========================================================================

void GLFWCALL
WindowRefreshFun(void) {
}

//========================================================================
// MousePosFun() - Mouse position callback function
//========================================================================

void GLFWCALL
MousePosFun(int x, int y) {
}

//========================================================================
// MouseButtonFun() - Mouse button callback function
//========================================================================

void GLFWCALL
MouseButtonFun(int button, int action) {
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
    if(!glfwOpenWindow(this->w, this->h, 0,0,0,0, this->bpp, 0, mode))
    {
        glfwTerminate();
    }

    // Set window title
    glfwSetWindowTitle(title);
    // Enable sticky keys
    glfwEnable(GLFW_STICKY_KEYS);
    // Enable mouse cursor (only needed for fullscreen mode)
    glfwEnable(GLFW_MOUSE_CURSOR);
    // Disable automatic event polling
    //glfwDisable(GLFW_AUTO_POLL_EVENTS);

    // Set callback functions
    glfwSetWindowSizeCallback( WindowSizeFun );
    glfwSetWindowRefreshCallback( WindowRefreshFun );
    glfwSetMousePosCallback( MousePosFun );
    glfwSetMouseButtonCallback( MouseButtonFun );
    
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
}

int
window::clear(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

int
window::cleardepth(void) {
    glClear(GL_DEPTH_BUFFER_BIT);
}

int
window::clearcolor(void) {
    glClear(GL_COLOR_BUFFER_BIT);
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
window::swapbuffers(void) {
    glfwSwapBuffers();
}

bool
window::isfinished(void) {
	return glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void
window::eventhandler(void) {
}

bool
window::getkeystate(int keysym) {
	return keys[keysym];
}
