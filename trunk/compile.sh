#!/bin/sh

HOMEDIR=`pwd`
BASELIBRARYDIR="$HOMEDIR/BaseLibrary/"
FACTORYDIR="$HOMEDIR/Factory/"
INTERPRETERDIR="$HOMEDIR/Interpreter/"
RELEASEDIR="$HOMEDIR/Release/"

PLUGINS=`ls $FACTORYDIR`

SCONSCOMPILE="-Q"
SCONSCLEAN="-c"

if [ "$#" -gt 0 ];
then
	if [ $1 = "clean" ];
	then
		SCONSARGS=$SCONSCLEAN
	else
		SCONSARGS=$SCONSCOMPILE
	fi
else
	SCONSARGS=$SCONSCOMPILE
fi

cd $BASELIBRARYDIR
scons $SCONSARGS
#temporal
cp libvasik.dylib $RELEASEDIR

cd $FACTORYDIR
for plugin in $PLUGINS
do
	cd $FACTORYDIR/$plugin
	scons $SCONSARGS
	#temporal
	cp *.so $RELEASEDIR
done

cd $INTERPRETERDIR
scons $SCONSARGS
#temporal
cp player $RELEASEDIR
