#!/bin/bash
# apk-get-package.sh - Returns the package name (com.blah.app) of an APK

INFO=$(aapt dump badging $1 2>/dev/null | grep "package" | cut -d"'" -f 2)

echo $INFO
