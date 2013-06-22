#!/bin/bash
# HgHash.sh - Returns the hash part of the Hg Version, otherwise 0

VAR=$(hg summary 2>/dev/null | grep "parent:" | awk '{split($2,Array,":");print Array[2]}')

if [ -n "$VAR" ]
then
	echo "$VAR"
else
	echo "0"
fi

exit 0
