#include "TScript.h"

lua_State*
TScript::state;

void
TScript::changedir(void) {
#ifdef __MACOSX__   
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

void
TScript::load(const char *name) {
	int status;

	// change dir
	changedir();

	// log date&time
	char timestamp[100];  
	time_t mytime;  
	struct tm *mytm;  
	mytime=time(NULL);  
	mytm=localtime(&mytime);  

	strftime(timestamp,sizeof(timestamp),"%a, %d %b %Y %H:%M:%S %z",mytm); 
	LOGTHIS("%s",timestamp);
	
	LOGTHIS("%s","Initializing scripting system");
	// Initialize Lua 
	state = lua_open();
	
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

void
TScript::dumpstack(void) {
	int i;
	int top = lua_gettop(state);  
  
	printf("total in stack %d\n",top);  
   
	for (i = 1; i <= top; i++)  {  
		int t = lua_type(state, i);  
		printf("%2i: ",i);
		switch (t) {
			case LUA_TSTRING:  /* strings */  
				printf("string\t'%s'\n", lua_tostring(state, i));  
				break;  
			case LUA_TBOOLEAN:  /* booleans */  
				printf("boolean\t'%s'\n",lua_toboolean(state, i) ? "true" : "false");  
				break;  
			case LUA_TNUMBER:  /* numbers */  
				printf("number\t'%g'\n", lua_tonumber(state, i));  
				break;  
			default:  /* other values */  
				printf("%s\n", lua_typename(state, t));  
				break;  
		}  
	}  
}
