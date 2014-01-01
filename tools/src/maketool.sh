#!/bin/bash
# maketool.sh - Simple Shell Script that compiles a tool for the current platform #

SCRIPT=`readlink -f "$0"`

SCRIPT_DIR=`dirname "$SCRIPT"`
SCRIPT_BASE=`basename "$SCRIPT" .sh`
SCRIPT_FILE=`basename "$SCRIPT"`

if [ "$1" == "" ]; then
	echo "USAGE: $SCRIPT_FILE ToolName"
	exit 1
fi

ROOT_NAME=../bin/"$1"

ARCH=`uname -m`
SUBARCH=`uname -i`

if [ "$WINDIR" != "" ]; then
	EXE="$ROOT_NAME".exe
else
if [ "$SUBARCH" != "unknown" ]; then
	EXE="$ROOT_NAME"_"$ARCH"_"$SUBARCH"
else
	EXE="$ROOT_NAME"_"$ARCH"
fi
fi

#CFLAGS="-O3 -s"
CFLAGS="-g"

# src, GEL and gel, since some file systems don't support upper case dirs #
INCLUDES="-I../../src -I../../src/GEL3"

mkdir -p obj
gcc -c $INCLUDES -D STBI_NO_WRITE ../../src/GEL3/External/STB/stb_image.c "$CFLAGS" -o obj/stb_image.c.o -static
gcc -c $INCLUDES ../../src/GEL3/External/STB/stb_image_write.c "$CFLAGS" -o obj/stb_image_write.c.o -static

g++ $INCLUDES "$1"/"$1".cpp obj/*.o ../../src/External/RectangleBinPack/*.cpp "$CFLAGS" -o "$EXE" -static

exit $?
