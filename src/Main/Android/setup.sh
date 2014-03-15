#!/bin/bash

export JAVA_HOME="/usr/lib/jvm/java-1.6.0-openjdk-amd64/jre"
export PATH="/opt/android-sdk/tools:/opt/android-sdk/platform-tools:/opt/android-ndk:$PATH"

echo "** Android Variables Set **"
echo "Don't forget to run: make TARGET_FILE=target/Common/makefile_android"
echo "(and make.sh inside src/GEL3Graphics/Render/Embedded/GLSL)"

