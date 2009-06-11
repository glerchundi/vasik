#include "imagesystem.h"

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) { 
	if(fif != FIF_UNKNOWN) { 
		LOGTHIS("%s Format", FreeImage_GetFormatFromFIF(fif)); 
	} 
	LOGTHIS("%s",message);
} 

imagesystem::imagesystem() {
}

imagesystem::~imagesystem() {
}

void imagesystem::init(void) {
	FreeImage_Initialise();
	FreeImage_SetOutputMessage(FreeImageErrorHandler);
}

void imagesystem::quit(void) {
	int i;
	for(i = 0 ; i < images.size() ; i++) {
		MYBITMAP *dib = images.get(i);
		if(dib->bitmap) FreeImage_Unload(dib->bitmap);
		delete dib;
	}
	FreeImage_DeInitialise();
}

void imagesystem::load(char *name, char *filename) {
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; 

	fif = FreeImage_GetFileType(filename, 0); 
	if(fif == FIF_UNKNOWN) { 
		fif = FreeImage_GetFIFFromFilename(filename); 
	} 
	
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		MYBITMAP *dib = new MYBITMAP();
		dib->bitmap = FreeImage_Load(fif, filename);//, flag); 
		if(dib->bitmap) 
			images.add(name,dib);
		else
			delete dib;
	}
}

void imagesystem::save(char *name) {
	char *name_with_extension;
	
	name_with_extension = (char *)malloc((strlen(name)+4)*sizeof(char));
	sprintf(name_with_extension,"%s.bmp",name);
	
	MYBITMAP *dib = images.get(name);
	
	if (FreeImage_Save(FIF_BMP, dib->bitmap, name_with_extension,BMP_SAVE_RLE)) {
		LOGTHIS("%s saved successfully",name_with_extension);
	}
}

void imagesystem::create(char *name, int width, int height, int bpp) {
	MYBITMAP *dib = new MYBITMAP();
	dib->bitmap = FreeImage_Allocate(width, height, bpp);
	if(dib->bitmap) 
		images.add(name,dib);
	else
		delete dib;
}

void imagesystem::checker(char *name, int repeatx, int repeaty) {
	MYBITMAP *dib = images.get(name);
	Checker::doit(dib->bitmap, repeatx, repeaty);
}

void imagesystem::perlin(char *name, float ifreq, float persistence, int octaves) {
	MYBITMAP *dib = images.get(name);
	Perlin::doit(dib->bitmap, ifreq, persistence, octaves);
}

void imagesystem::ogl_load(char *name) {
	BYTE *bits;
	unsigned int width,height,bpp;
	MYBITMAP *dib;
	
	dib    = images.get(name);	
	width  = FreeImage_GetWidth(dib->bitmap);
	height = FreeImage_GetHeight(dib->bitmap);
	bpp    = FreeImage_GetBPP(dib->bitmap);
	bits   = FreeImage_GetBits(dib->bitmap);
	
	glGenTextures(1, &dib->texID);
	glBindTexture(GL_TEXTURE_2D, dib->texID);

	// Create MipMapped Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	if(bpp == 24)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, bits);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bits);
}

void imagesystem::ogl_bind(char *name) {
	glBindTexture(GL_TEXTURE_2D, images.get(name)->texID);
}