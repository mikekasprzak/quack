#!/bin/bash
# build.sh - Build and install the current project

# Halt on any errors #
set -e

# Build Process #
ndk-build -j
ant debug
ant installd
./run.sh
