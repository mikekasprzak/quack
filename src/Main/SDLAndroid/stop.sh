#!/bin/bash
# stop.sh - Stop the current APK project (assuming it's running)

./apk-stop.sh `./apk-get-debugapk.sh`
