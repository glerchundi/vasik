#include "effect.h"

WRAPPLUGIN(effect)
WRAPFUNC0(_int,render)

#define MAX_CUBES 196

float cube_altu[MAX_CUBES];
float cube_tmp1[MAX_CUBES];
float cube_tmp2[MAX_CUBES];

effect::effect() {
    SHAREPLUGIN(effect);
    SHAREFUNC(render);

    PLUGINNAME("effect");
    PLUGINDESCR("some effect description");
}

effect::~effect() {
}

void effect::init(void) {
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

void effect::initplugin(char *name, TPlugin *plugin) {
    this->addplugin(name, plugin);
}

void effect::quit(void) {
}

/* RANDOMIZE */

float random(int max_value)
{
    return (float)(rand() % max_value);
}

/*******************************************************************
    BUILD LISTS
*******************************************************************/
//GLuint cube;

void DaCube(float altura)                   // Build Box Display List
{ 
    glBegin(GL_QUADS);                          // Start Drawing Quads
        glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  altura,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  altura,  1.0f);
        // Back Face
        glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  altura, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  altura, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  altura, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  altura,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  altura,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  altura, -1.0f);
        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  altura, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  altura,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  altura,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  altura, -1.0f);
    glEnd();

}

/* SCALE SYNCH */

float num;

void PutCubes(long time)
{
    int i,j,cnt = 0;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
    for(i = -14 ; i < 14 ; i+=2)
    {
        for(j = -14 ; j < 14 ; j+=2,cnt++)
        {
            glLoadIdentity();
            gluLookAt(6.95f,12.0f,-15.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
            glTranslatef((float)j,0.0f,(float)i);
            DaCube(cube_altu[cnt]);
        }
    }
    cnt = 0;

    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    glPolygonMode(GL_FRONT,GL_LINE);
    glColor3f(0.0f,0.0f,0.0f);
    for(i = -14 ; i < 14 ; i+=2)
    {
        for(j = -14 ; j < 14 ; j+=2,cnt++)
        {
            glLoadIdentity();
            gluLookAt(6.95f,12.0f,-15.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
            glTranslatef((float)j,0.0f,(float)i);
            DaCube(cube_altu[cnt]);
        }
    }
    cnt = 0;

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glDisable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHTING);
}

int effect::setup(void)
{
    GLfloat fogColor[4]         = {0.25f, 0.25f, 0.25f, 1.0f};

    GLfloat LightAmbient[]      = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    GLfloat LightPosition[]     = { 5.0f, 13.0f, -10.0f, 1.0f }; 
    GLfloat LightDiffuse[]      = { 1.0f, 0.25f, 0.25f, 1.0f };

    ret = execute("timer","createTimer",NULL);
    timerId = ret->_int;
    ret = execute("window","getwidth",NULL);
    windowWidth = ret->_int;
    ret = execute("window","getheight",NULL);
    windowHeight = ret->_int;

    vars[0]._int    = windowWidth;
    vars[1]._int    = windowHeight;
    vars[2]._bool   = true;
    execute("window","setupview",vars);

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    srand((unsigned)time(NULL));

    // generation cube altures
    for(int i = 0 ; i < MAX_CUBES ; i++)
        cube_altu[i] = random(4);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); 
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); 
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   

    glFogi(GL_FOG_MODE, GL_LINEAR);     // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 2.0f);               // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 15.0f);                // Fog Start Depth
    glFogf(GL_FOG_END, 25.0f);              // Fog End Depth

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glClearColor(0.25f, 0.25f, 0.25f,0.0f); 

    vars[0]._int = timerId;
    execute("timer","start",vars);

    return 0;
}

int effect::render(void)
{
    int i;

    if(_setup == false)
    {
        this->setup();
        _setup = true;
    }
    

    vars[0]._int = timerId;
    ret = execute("timer","getMs",vars);
    ms  = ret->_int;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

    vars[0]._int    = windowWidth;
    vars[1]._int    = windowHeight;
    vars[2]._bool   = true;
    execute("window","setupview",vars);

    vars[0]._int    = 20;
    vars[1]._int    = 20;
    vars[2]._pchar  = "THIS IS MY...testing font....";
    execute("font","drawText",vars);

    vars[0]._int    = windowWidth;
    vars[1]._int    = windowHeight;
    vars[2]._bool   = false;
    execute("window","setupview",vars);

    glDisable(GL_BLEND);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    for(i=0;i< MAX_CUBES ; i++)
        cube_tmp1[i] = cube_altu[i] + 1.0f + sin(ms/125.0f + i);

    for(i=0;i<MAX_CUBES ; i++)
    {
        cube_tmp2[i] = cube_altu[i];
        cube_altu[i] = cube_tmp1[i];
    }
    PutCubes(ms);
    
    for(i=0;i<MAX_CUBES ; i++)
        cube_altu[i] = cube_tmp2[i];
    
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glFinish();
    glFlush();

   return 0;
}
