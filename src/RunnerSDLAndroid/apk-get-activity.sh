#!/bin/bash
# apk-get-activity.sh - Returns the activity name (MainActivity) of an APK

INFO=$(aapt dump badging $1 2>/dev/null | grep "launchable-activity" | cut -d"'" -f 2 | cut -d"." -f 4)

echo $INFO
