/* File : sdl.i */
%module sdl

%{
#include "sdl.h"
#include "keysym.h"
%}

/* Let's just grab the original header file here */
%include "sdl.h"
%include "keysym.h"

