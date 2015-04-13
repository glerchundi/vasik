After going through different GNU/Linux distributions, I've decided to stop moving and use Ubuntu 8.10 (Intrepid Ibex) as my default GNU/Linux desktop choice. All these steps were followed on a Ubuntu 8.10 (Intrepid Ibex). It's important to install all packages in a place where the compiler and the linker can find. In the example below include files are installed in /usr/local/include/ and libraries in /usr/local/lib/.

  1. I don't think that you'll try to use this package without having a GNU/Linux that doesn't ship with g++/ld/etc... .
  1. If needed, install python. Installed by default in a typical GNU/Linux installation.
  1. Install SCons (http://www.scons.org):
```
    tar xvfz scons-1.2.0.tar.gz
    cd scons-1.2.0/
    sudo python setup.py install
```
  1. Install Swig (http://www.swig.org):
```
    tar xvfz swig-1.3.39.tar.gz
    cd swig-1.3.39/
    ./configure
    make
    sudo make install
```
  1. Install Lua (http://www.lua.org):
```
    tar xvfz lua-5.1.4.tar.gz
    cd lua-5.1.4/
    make linux
    sudo make install
```

Optional to run 'demosystem':

  1. Install GLFW (http://glfw.sourceforge.net):
    * Prerequisites to build GLFW:
```
    sudo apt-get install libglu1-mesa-dev libgl1-mesa-dev mesa-common-dev (or apt-get install libglu-dev)
```
    * GLFW package:
```
    tar xvfz glfw-2.6.tar.gz
    cd glfw/
    make x11-gcc
    sudo make x11-install
```
  1. Install FreeImage (http://freeimage.sourceforge.net): **IMPORTANT! You need to have Mac OS X 10.3.9 SDK installed on you system, don't forget to click on the checkbox when installing XCode Tools!**
```
    unzip FreeImage3120.zip
    cd FreeImage/
    make
    sudo make install
```
  1. Install FreeType (http://freetype.sourceforge.net):
```
    tar xvfz freetype-2.3.9.tar.gz
    cd freetype-2.3.9/
    ./configure
    make
    sudo make install
    sudo ln -s /usr/local/include/freetype2/freetype/ /usr/local/include/freetype (to fix bad header placing...)
```
  1. Install FFTW3 (http://www.fftw.org)
```
    ./configure
    make
    sudo make install
```
  1. Install FMOD 3.75 (http.//www.fmod.org)
```
    tar xvfz fmodapi375linux.tar.gz
    cd fmodapi375linux/
    sudo cp api/inc/* /usr/local/include/
    sudo cp api/libfmod-3.75.so /usr/local/lib/
```
Hei! If you've achieved correctly those steps...You're ready to run:
```
tar xvfz vasik-0.1.0.tar.gz
cd vasik-0.1.0/
./compile.sh
cd Release/
vim/emacs/WhateverYouUseToEditFiles data/script.lua (modify the script)
./player (run! run! run!)
```

You're done!!! Happy Vasik`*` coding!