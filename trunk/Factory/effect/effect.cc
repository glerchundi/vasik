#include "effect.h"

effect::effect()
{
}

effect::~effect()
{
}

int width  = 640;
int height = 480;
int i;
float step = 640.0/512.0;
float xrot=0.0,yrot=0.0,zrot=0.0;

void effect::init(void)
{
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void effect::quit(void) {
}

void effect::render(void)
{
	this->render(NULL);
}

void effect::render(double* data)
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0,0,width,height);						// Reset The Current Viewport	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix	glLoadIdentity();							// Reset The Projection Matrix	glOrtho(0.0f,width,height,0.0f,-1.0f,1.0f);				// Create Ortho 640x480 View (0,0 At Top Left)	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix	glLoadIdentity();							// Reset The Modelview Matrix
	
	if(data != NULL)
	{
   		//glDisable(GL_TEXTURE_2D);
		for(i = 0 ; i < 512 ; i++)
		{
			float d = data[i]/65535.0;
			glBegin(GL_QUADS);
				glVertex2f(step*i,240.0+d);
				glVertex2f(step*i,240-d);
				glVertex2f(step*(i+1),240-d);
				glVertex2f(step*(i+1),240.0+d);			
			glEnd(); 
		}
		
    	//glEnable(GL_TEXTURE_2D);	
	}
	
	glClear(GL_DEPTH_BUFFER_BIT);
  
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
	
    glTranslatef( 0.0f, 0.0f, -5.0f );

    glRotatef( xrot, 1.0f, 0.0f, 0.0f); 
    glRotatef( yrot, 0.0f, 1.0f, 0.0f); 
    glRotatef( zrot, 0.0f, 0.0f, 1.0f); 

    glBegin(GL_QUADS);
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f, -1.0f, 1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f,  1.0f, 1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f,  1.0f, 1.0f );

      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );

      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f,  1.0f,  1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  1.0f,  1.0f,  1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );

      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f, -1.0f,  1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f,  1.0f );

      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f,  1.0f, -1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,  1.0f,  1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f,  1.0f );

      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f,  1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f,  1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
    glEnd( );

	xrot += 0.05;
	yrot += 0.05;
	yrot += 0.05;
}

#include <stdio.h>
void effect::print(void)
{
	/*
	puts("kaiiiiiixoooooooo");
	puts("       AVG   VAR");
	for(i = 0 ; i < 512 ; i++) {
		printf("%3i: %5f %5f\n",i,davg[i],dvar[i] - davg[i]*davg[i]);
	}
	*/
}
