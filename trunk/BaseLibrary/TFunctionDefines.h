#ifdef __MACOSX__
#elif  __LINUX__
#elif  __WIN32__
    #define snprintf _snprintf
    #define vsnprintf _vsnprintf
    #define strcasecmp _stricmp
    #define strncasecmp _strnicmp
#endif
