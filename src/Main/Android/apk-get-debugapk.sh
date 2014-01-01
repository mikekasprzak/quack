#!/bin/bash
# apk-get-debugapk.sh - Get the name of the Debug APK file

PACKAGE=bin/`./apk-get-project.sh $1`-debug.apk

echo $PACKAGE
