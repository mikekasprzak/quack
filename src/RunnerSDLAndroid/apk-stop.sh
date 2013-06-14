#!/bin/bash
# apk-stop.sh - Stop the specificed package on remote device (assuming it's running)

PACKAGE=`./apk-get-package.sh $1`

adb shell am force-stop $PACKAGE
