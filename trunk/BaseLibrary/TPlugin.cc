#include "TPlugin.h"

TPlugin::TPlugin() {
    funcs   = new TList<ptFunc>();
    plugins = new TList<TPlugin*>();
}

TPlugin::~TPlugin() {
}

param*
TPlugin::execute(char *plugin, char *func, param* vars) {
	TPlugin *p = plugins->get(plugin);
	return p->execute(func, vars);	
}

param*
TPlugin::execute(char *func, param* vars) {
    ptFunc f = funcs->get(func);
    return f(vars);
}

void
TPlugin::addfunc(char *func, ptFunc f) {
	funcs->add(func, f);		
}

void
TPlugin::addplugin(char *plugin, TPlugin *p) {
    plugins->add(plugin, p);
}

/*

TPlugin*
TPlugin::getplugin(char *plugin) {
	swig_lua_userdata *data;

	lua_State *state = TScript::state;
	TPlugin *p;
	//
	// Access to static members
	// x = module.classname_staticmember(arg1, arg2, ...)
	// In our case: plugin = effect.effect_getmodule(true/false);
	//
	if(createnew) {
		snprintf(cmd, MAXCHAR, "%s_getmodule", plugin);
	} else {
		snprintf(cmd, MAXCHAR, "getinstance");
	}	

	lua_getglobal(state, plugin);
	if(lua_type(state, -1) != LUA_TTABLE) {
		LOGTHIS("%s is not loaded", plugin);
	}

	lua_getfield(state, -1, cmd);
	if(lua_type(state, -1) != LUA_TFUNCTION) {
		LOGTHIS("%s module has no '%s' function", plugin, cmd);
	}

	// remove 'plugin' table from stack
	lua_replace(state, -2);
	//lua_pushboolean(state, createnew);

	if(lua_pcall(state, 1, 1, 0) != 0) {
		LOGTHIS("Error executing '%s': %s", cmd, lua_tostring(state, -1));
	}

	data 	= (swig_lua_userdata *)lua_touserdata(state,1);
	p		= (TPlugin *)data->ptr;

	return plugins->get(plugin);
}
*/
