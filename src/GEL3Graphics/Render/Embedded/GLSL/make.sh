#!/bin/bash

mkdir -p Output

for file in *.json ; do
	../../../../../tools/bin/Text2C $file Output/$file.c "_json"
done

for file in *.glsl ; do
	../../../../../tools/bin/Text2C $file Output/$file.c "_glsl"
done

exit 0
