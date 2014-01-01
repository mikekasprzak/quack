#!/bin/bash
# apk-get-releaseapk.sh - Get the name of the Release APK file

PACKAGE=bin/`./apk-get-project.sh $1`-release.apk

echo $PACKAGE
