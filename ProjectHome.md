### Introduction ###

![http://lh3.ggpht.com/_AAqg2rtgP-E/SjbE5rzGXBI/AAAAAAAAAIE/hvASfd2X-QQ/s800/logo.png](http://lh3.ggpht.com/_AAqg2rtgP-E/SjbE5rzGXBI/AAAAAAAAAIE/hvASfd2X-QQ/s800/logo.png)

Vasik`*` is a plugin-based framework in which plugins are written in C/C++ and are interpreted over a main lua script.

Vasik`*` relies on:
  * **Lua** (http://www.lua.org): A programming language used as scripting language.
  * **SWIG** (http://www.swig.org): Simplified wrapper and interface generator for wrapping plugins into the scripting language.
  * **SCons** (http://www.scons.org): SCons is an Open Source software construction tool—that is, a next-generation build tool. Think of SCons as an improved, cross-platform substitute for the classic Make utility with integrated functionality similar to autoconf/automake and compiler caches such as ccache. In short, SCons is an easier, more reliable and faster way to build software.

Lua is used as the scripting language to manage different kind of plugins. And the plugins, coded in C++, are wrapped using SWIG.

As an example 'demosystem' plugin is created and distributed into the Vasik`*` package. To be able of using it some external libraries are needed:
  * **GLFW** (http://glfw.sourceforge.net): A cross-platform OpenGL Framework.
  * **FMOD** (http://www.fmod.org): A world-leading library and toolkit for the creation and playback of interactive audio.
  * **FreeImage** (http://freeimage.sourceforge.net/): FreeImage is an Open Source library project for developers who would like to support popular graphics image formats like PNG, BMP, JPEG, TIFF and others as needed by today's multimedia applications. FreeImage is easy to use, fast, multithreading safe, compatible with all 32-bit versions of Windows, and cross-platform (works both with Linux and Mac OS X).
  * **FreeType** (http://freetype.sourceforge.net/): FreeType 2 is a software font engine that is designed to be small, efficient, highly customizable, and portable while capable of producing high-quality output (glyph images). It can be used in graphics libraries, display servers, font conversion tools, text image generation tools, and many other products as well.
  * **FFTW** (http://www.fftw.org/): FFTW is a C subroutine library for computing the discrete Fourier transform (DFT) in one or more dimensions, of arbitrary input size, and of both real and complex data (as well as of even/odd data, i.e. the discrete cosine/sine transforms or DCT/DST).

### Download ###
<a href='http://vasik.googlecode.com/files/vasik-0.1.0.zip'><img src='http://lh6.ggpht.com/_AAqg2rtgP-E/SjexwfCtbRI/AAAAAAAAAIQ/N-RCy47dhmM/s800/zip.png' /></a>

### Example ###

First Vasik`*` release comes with support for Mac OS X, GNU/Linux and Microsoft Windows. Here goes an example script with three different screenshots representing the same script version running in different machines:

```
require('demosystem');

-- CREATE OBJECTS
window      = demosystem.window();
soundsys    = demosystem.soundsystem();
fxcubes     = demosystem.effect();
scheduler   = demosystem.scheduler();
timer       = demosystem.timer();
font        = demosystem.font();
shell       = demosystem.shell();

-- INIT WINDOW
window:init('Vasik*',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:loadstream("oasis","data/Oasis - Wonderwall.mp3");
soundsys:playstream("oasis");

-- INIT TIMER
timer:init();

-- INIT FONT
font:initplugin("window", window);
font:init();
font:setFont("data/Fixedsys500c.ttf",10);

-- INIT SHELL
shell:initplugin("window", window);
shell:initplugin("timer", timer);
shell:initplugin("font", font);
shell:init();

-- INIT EFFECTS
fxcubes:initplugin("window", window);
fxcubes:initplugin("timer", timer);
fxcubes:initplugin("font", font);
fxcubes:init();

-- INIT SCHEDULER
scheduler:initplugin("window", window);
scheduler:initplugin("timer", timer);
scheduler:initplugin("cubes", fxcubes);
scheduler:initplugin("shell", shell);
scheduler:init(1);

scheduler:addfx(0,0,-1,"cubes","render", nil);
scheduler:addfx(0,0,-1,"shell","render",nil);

scheduler:play(0);

shell:quit();
font:quit();
timer:quit();
scheduler:quit();
fxcubes:quit();
soundsys:quit();
window:quit();

```

Script run on Mac OS X:

![http://lh5.ggpht.com/_AAqg2rtgP-E/SjbE5hj4r7I/AAAAAAAAAIA/m-I5iBQR2XE/s800/vasik_macosx.png](http://lh5.ggpht.com/_AAqg2rtgP-E/SjbE5hj4r7I/AAAAAAAAAIA/m-I5iBQR2XE/s800/vasik_macosx.png)

Script run on GNU/Linux:

![http://lh3.ggpht.com/_AAqg2rtgP-E/SjeZUJiHxDI/AAAAAAAAAII/yqQHbkVSzss/s800/vasik_gnulinux.png](http://lh3.ggpht.com/_AAqg2rtgP-E/SjeZUJiHxDI/AAAAAAAAAII/yqQHbkVSzss/s800/vasik_gnulinux.png)

Script run on Microsoft Windows:

![http://lh3.ggpht.com/_AAqg2rtgP-E/SjbE5Q8_KiI/AAAAAAAAAH8/JIx7x9WPt6c/s800/vasik_win32.png](http://lh3.ggpht.com/_AAqg2rtgP-E/SjbE5Q8_KiI/AAAAAAAAAH8/JIx7x9WPt6c/s800/vasik_win32.png)