#include "glwindow.h"

//========================================================================
// WindowSizeFun() - Window size callback function
//========================================================================

void GLFWCALL WindowSizeFun( int w, int h )
{
    /*
    width  = w;
    height = h > 0 ? h : 1;
    do_redraw = 1;
    */
}

//========================================================================
// WindowRefreshFun() - Window refresh callback function
//========================================================================

void GLFWCALL WindowRefreshFun( void )
{
}

//========================================================================
// MousePosFun() - Mouse position callback function
//========================================================================

void GLFWCALL MousePosFun( int x, int y )
{
}

//========================================================================
// MouseButtonFun() - Mouse button callback function
//========================================================================

void GLFWCALL MouseButtonFun( int button, int action )
{
}

glwindow::glwindow(void) {
	this->finished = false;
	memset(keys,0,512);
}

glwindow::~glwindow() {
}

int	 glwindow::init(const char *title, int width, int height, int bpp, bool full) {
	this->w 	= width;
	this->h 	= height;
	this->bpp 	= bpp;
	this->full	= full;
	this->view_w = this->w;
	this->view_h = this->h;

	LOGTHIS("Opening window: w=%i h=%i bpp=%i full=%i",this->w,this->h,this->bpp,this->full);

    // Initialise GLFW
    glfwInit();

	int mode = (this->full) ? GLFW_FULLSCREEN : GLFW_WINDOW;

    // Open OpenGL window
    if( !glfwOpenWindow( this->w, this->h, 0,0,0,0, this->bpp, 0, mode ) )
    {
        glfwTerminate();
        return 0;
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
    
    this->setupgl(this->w,this->h);

    return 0;
}

void glwindow::quit(void) {
	LOGTHIS("%s","Closing window...");
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
	LOGTHIS("%s","Window closed");
}

void glwindow::setupgl(int width, int height) {
	/* Height / width ration */
    GLfloat ratio;
    /* Protect against a divide by zero */
	if( height == 0 )
		height = 1;
    ratio = (GLfloat)width/(GLfloat)height;
    /* Setup our viewport. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Set our perspective */
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode(GL_MODELVIEW);
    /* Reset The View */
    glLoadIdentity();
}

void glwindow::swapbuffers(void) {
    glfwSwapBuffers();
}

bool glwindow::isfinished(void) {
	return glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void glwindow::eventhandler(void) {
    //this->finished = glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
}

bool glwindow::getkeystate(int keysym) {
	return keys[keysym];
}
