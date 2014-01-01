#!/bin/bash
# apk-run.sh - Run the specificed package on remote device (assuming it's installed)

PACKAGE=`./apk-get-package.sh $1`
ACTIVITY=`./apk-get-activity.sh $1`

adb shell am start -n $PACKAGE/$PACKAGE.$ACTIVITY
