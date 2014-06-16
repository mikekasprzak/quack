#!/bin/sh
# genfilelist.sh - Generate a files.txt file

TREETOOL=`readlink -f tools/TreeTool.sh`

(cd src/Quack/QuackLib; $TREETOOL . % >files.txt)
(cd src/GEL3Graphics/Render/Embedded; $TREETOOL . % >files.txt)

(cd project; $TREETOOL . % >files.txt)

exit 0
