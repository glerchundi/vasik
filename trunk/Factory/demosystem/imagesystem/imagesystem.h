#ifndef IMAGESYSTEM_H__
#define IMAGESYSTEM_H__

#include "TVasik.h"

#include "FreeImage.h"

#include "src/Noise.h"
#include "src/Checker.h"
#include "src/Perlin.h"

class MYBITMAP {
public:
	FIBITMAP     *bitmap;
	unsigned int texID;
};

class imagesystem : public TPlugin {
public:
    // construct & destruct
    imagesystem();
    ~imagesystem();
    // imagesystem func's
    void    initplugin(char *name, TPlugin *plugin);
	void    init(void);
	void    quit(void);
	// other wrapping func's
	// handle
	void    load(char *name, char *filename);
	void    save(char *name);
	// create
	void    create(char *name, int width, int height, int bpp);
	void    checker(char *name, int repeatx, int repeaty);
	void    perlin(char *name, float ifreq, float persistence, int octaves);
	// bind to opengl
	void    ogl_load(char *name);
	void    ogl_bind(char *name);		
private:
	// imagesystem var's
	TList<MYBITMAP*> images;
};

#endif
