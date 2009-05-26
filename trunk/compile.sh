#!/bin/bash

HOMEDIR=`pwd`
BASELIBRARYDIR="$HOMEDIR/BaseLibrary/"
FACTORYDIR="$HOMEDIR/Factory/"
INTERPRETERDIR="$HOMEDIR/Interpreter/"
RELEASEDIR="$HOMEDIR/Release/"

PLUGINS=`ls $FACTORYDIR 2> /dev/null`

SCONSCOMPILE="-Q"
SCONSCLEAN="-c"

function DoSCONS {
	cd $1
	if [ $ARG = "compile" ]; then
		echo "Compiling $1 ..."
		scons $SCONSCOMPILE
		cp $2 $RELEASEDIR
	else
		echo "Cleaning $1 ..."
		scons $SCONSCLEAN
		if [ `ls -l $RELEASEDIR/$2 2> /dev/null | wc -l` -gt 0 ]; then
			rm $RELEASEDIR/$2
		fi
	fi
	echo ""
}

if [ "$#" -gt 0 ]; then
	if [ $1 = "clean" ]; then
		ARG="clean"
	elif [ $1 = "compile" ]; then
		ARG="compile"
	else
		echo "Unknown parameter passed."
		exit
	fi
else
	ARG="compile"
fi

DoSCONS $BASELIBRARYDIR "libvasik.dylib"
for plugin in $PLUGINS; do
	DoSCONS $FACTORYDIR/$plugin "*.so"
done
DoSCONS $INTERPRETERDIR "player"
