#!/bin/bash
# build.sh - Build and install the current project

ndk-build
ant debug
ant installd
./run.sh
