#!/bin/bash
# apk-get-project.sh - Get the project name

INFO=$(cat build.xml 2>/dev/null | grep "<project name" | cut -d'"' -f 2 )

echo $INFO
