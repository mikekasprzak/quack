#!/bin/sh
# genfilelist.sh - Generate a files.txt file

tools/TreeTool.sh src/Quack/QuackLib % >src/files.txt
tools/TreeTool.sh src/GEL3Graphics/Render/Embedded % >>src/files.txt

tools/TreeTool.sh project % >project/files.txt

exit 0
