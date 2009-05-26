#include "TVasik.h"

TVasik::TVasik() {
	this->changedir();
}

TVasik::TVasik(const char *name) {
	this->changedir();
	this->loadscript(name);
}

TVasik::~TVasik() {
}

void TVasik::changedir(void) {
#ifdef __APPLE__   
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
        // error!
    }
    CFRelease(resourcesURL);
    chdir(path);
#endif
}

void TVasik::loadscript(const char *name) {
	int status;
	
	// log date&time
	char *tmp;
	char buffer[256];
	time_t curtime;
	struct tm *loctime;
	curtime = time(NULL);
	loctime = localtime(&curtime);
	tmp     = asctime(loctime);
	strncpy(buffer,tmp,strlen(tmp)-1);
	LOGTHIS("%s",buffer);
	
	LOGTHIS("%s","Initializing scripting system");
	// Initialize Lua 
	lua_State *state = lua_open();
	
	// Load Lua libraries 
	luaL_openlibs(state);
	//luaopen_package();
	
	LOGTHIS("Loading %s script file",name);
	// Run a test script to exercise our new function 
	status = luaL_loadfile(state, name);
	if(status == 0) {
	    status = lua_pcall(state, 0, 0, 0);
	}

	if (status != 0) {
		LOGTHIS("%s", lua_tostring(state, -1));
    	lua_pop(state, 1);
		lua_gc(state, LUA_GCCOLLECT, 0);
	}
	 
	// Clean up Lua
	lua_close(state);
}
