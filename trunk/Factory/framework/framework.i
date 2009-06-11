/* File : framework.i */
%module framework

%{
#include "framework.h"
%}

/* Let's just grab the original header file here */
%include "TPlugin.h"

%include "framework.h"
