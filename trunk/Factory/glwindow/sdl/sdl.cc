#include "sdl.h"

/*
// SetTitle(title)

int SetTitle(lua_State *state)
{
	SDL_WM_SetCaption(lua_tostring(state,1),NULL);
	return 0;
}
*/
sdl::sdl(void) {
	this->finished = false;
	memset(keys,0,512);
}

sdl::~sdl() {
}

int	 sdl::init(const char *title, int width, int height, int bpp, bool full) {
	this->w 	= width;
	this->h 	= height;
	this->bpp 	= bpp;
	this->full	= full;

	this->view_w = this->w;
	this->view_h = this->h;

	LOGTHIS("Opening window: w=%i h=%i bpp=%i full=%i",this->w,this->h,this->bpp,this->full);
	
	this->info = NULL;
	int flags = 0;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOGTHIS("Video initialization failed: %s",SDL_GetError());
		exit(-1);
	}
	
	this->info = SDL_GetVideoInfo();

	if(!this->info)
	{
		LOGTHIS("Video query failed: %s",SDL_GetError());
		exit(-1);
	}

	this->bpp = this->info->vfmt->BitsPerPixel;

	flags = SDL_OPENGL;
	
	if(this->full)
		flags |= SDL_FULLSCREEN;

	flags |= SDL_DOUBLEBUF;
	flags |= SDL_HWSURFACE;

	if(SDL_SetVideoMode(this->w,this->h,this->bpp,flags) == 0)
	{
		LOGTHIS("Video mode set failed: %s",SDL_GetError());
		exit(-1);
	}	
	
	SDL_WM_SetCaption(title,NULL);
	
	this->setupgl(this->w,this->h);

	return 0;
}

void sdl::quit(void) {
	LOGTHIS("%s","Closing window...");
	SDL_Quit();
	LOGTHIS("%s","Window closed");
}

void sdl::setupgl(int width, int height) {
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

void sdl::swapbuffers(void) {
	SDL_GL_SwapBuffers();
}

bool sdl::isfinished(void) {
	return finished;
}

void sdl::eventhandler(void) {
	SDL_Event event;
	
	while(SDL_PollEvent(&event)) 
	{
		switch(event.type) 
		{
			case SDL_KEYDOWN:
				keys[event.key.keysym.sym] = true;
				if(event.key.keysym.sym == SDLK_ESCAPE) 
					this->finished = true;
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.sym] = false;
				break;
			case SDL_QUIT:
				this->finished = true;
				break;
		}
	}
}

bool sdl::getkeystate(int keysym) {
	return keys[keysym];
}
