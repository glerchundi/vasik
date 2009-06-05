/* File : maths.i */
%module maths

%{
#include "maths.h"
%}

/* Let's just grab the original header file here */
%include "TPlugin.h"
%include "maths.h"
%include "dsp.h"
