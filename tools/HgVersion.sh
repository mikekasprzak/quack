#!/bin/bash
# HgVersion.sh - Returns the version part of the Hg Version, otherwise 0

#VAR=$(hg summary 2>/dev/null | grep "parent:" | sed s/"parent: "//)
#VAR=$(hg summary 2>/dev/null | grep "parent:" | awk '{print $2}')

VAR=$(hg summary 2>/dev/null | grep "parent:" | awk '{split($2,Array,":");print Array[1]}')

if [ -n "$VAR" ]
then
	echo "$VAR"
else
	echo "0"
fi

exit 0
