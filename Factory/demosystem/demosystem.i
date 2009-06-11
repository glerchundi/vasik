/* File : demosystem.i */
%module demosystem

%{
#include "imagesystem/imagesystem.h"
#include "soundsystem/soundsystem.h"
#include "scheduler/scheduler.h"
#include "timer/timer.h"
#include "maths/maths.h"
#include "window/window.h"
#include "font/font.h"
#include "shell/shell.h"
#include "effect/effect.h"
%}

/* Let's just grab the original header file here */
%include "TPlugin.h"

%include "imagesystem/imagesystem.h"
%include "soundsystem/soundsystem.h"
%include "scheduler/scheduler.h"
%include "timer/timer.h"
%include "maths/maths.h"
%include "window/window.h"
%include "font/font.h"
%include "shell/shell.h"
%include "effect/effect.h"
