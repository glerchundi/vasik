#include "TPlugin.h"

TPlugin::TPlugin() {
	this->linked = false;
}

TPlugin::TPlugin(char *plugin) {
	this->linked = false;
	this->LinkPlugin(plugin);
}

TPlugin::~TPlugin() {
}

void
TPlugin::LinkPlugin(char *plugin) {
	strncpy(this->pluginname, plugin, strlen(plugin));
}

void*
TPlugin::ExecuteFunction(char *func, ...) {
	va_list ap;

	memset(string, 0, MAXCHAR);
	sprintf(string, "%s:%s(", this->pluginname, func);
	
	puts(string);

	va_start(ap, func);
	while(*func != '\0') {
		sprintf(string, "%s%s,", string, va_arg(ap, char*));
	}
	va_end(ap);

	this->string[strlen(string)-1] = ')';
	this->string[strlen(string)  ] = ';';
	this->string[strlen(string)+1] = '\0';
}
