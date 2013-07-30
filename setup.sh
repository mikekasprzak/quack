#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system
#
# TODO: Make the SKU complain if the directory doesn't contain the project

DEFAULTDIR=target/Default
CONFIGDIR=config

# Are we running Windows? #
if [ "$WINDIR" != "" ]; then
	SYSTEM_SUFFIX=
else
	SYSTEM_SUFFIX=_`uname -s`
fi

echo "usage: `basename $0` [ProjectName] [target_sku] [target_makefile]"
echo ""

if [ -e "$CONFIGDIR/.project" ]; then
	echo "Warning! File \".project\" exists!"
	echo -n "Overwrite [type \"yes\"]? "
	read answer
	if [ "$answer" != "yes" ]; then
		echo "Exiting..."
		exit 1
	fi
fi

echo "Generating project settings..."
echo ""

mkdir -p $CONFIGDIR

if [ ! -n "$1" ]; then
	if [ -e "$CONFIGDIR/.project" ]; then
		PROJECT=`cat $CONFIGDIR/.project`
	else
		PROJECT=`cat $DEFAULTDIR/.project`
	fi

	while true; do
		echo -n "Project Name [$PROJECT]: "
		read answer
		if [ "$answer" != "" ]; then
			# Answer Given #
			if [ -e "target/SKU/$answer" ]; then
				PROJECT="$answer"
				break
			else
				echo "Error! $answer not found!"
				#exit -1
			fi		
		else
			# No Answer Given (Just pushed enter) #
			if [ -e "target/SKU/$PROJECT" ]; then
				break
			else
				echo "Error! $PROJECT not found!"
				#exit -1
			fi
		fi
	done
else
	if [ -e "target/SKU/$1" ]; then
		PROJECT=$1
	else
		echo "Error! $1 not found!"
		exit -1
	fi
fi  

echo "Project Name: $PROJECT"
rm -f $CONFIGDIR/.project
echo "$PROJECT" >$CONFIGDIR/.project
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.project
fi


# Target SKU Makefile #
if [ ! -n "$2" ]; then
	if [ -e "$CONFIGDIR/.sku" ]; then
		SKU=`cat $CONFIGDIR/.sku | awk '{print $1}'`
	elif [ -e "target/SKU/$PROJECT/.default" ]; then
		SKU=`cat target/SKU/$PROJECT/.default | awk '{print $1}'`
	else
		SKU="target/SKU/$PROJECT/`cat $DEFAULTDIR/default.sku`"
	fi

	while true; do
		echo -n "Target SKU [$SKU]: "
		read answer
		if [ "$answer" != "" ]; then
			# Answer Given #
			if [ -e "$answer" ]; then
				SKU="$answer"
				break
			elif [ -e "target/SKU/$PROJECT/$answer" ]; then
				SKU="target/SKU/$PROJECT/$answer"
				break
			else
				echo "Error! $answer and target/SKU/$PROJECT/$answer not found!"
				#exit -1
			fi
		else
			# No Answer Given (Just pushed enter) #
			if [ -e "$SKU" ]; then
				break
			elif [ -e "target/SKU/$PROJECT/$SKU" ]; then
				SKU="target/SKU/$PROJECT/$SKU"
				break
			else
				echo "Error! $SKU and target/SKU/$PROJECT/$SKU not found!"
				#exit -1
			fi
		fi
	done
else
	if [ -e "$2" ]; then
		SKU="$2"
	elif [ -e "target/SKU/$PROJECT/$2" ]; then
		SKU="target/SKU/$PROJECT/$2"
	else
		echo "Error! $2 and target/SKU/$PROJECT/$2 not found!"
		exit -1
	fi
fi

if [ -e "$CONFIGDIR/.sku_all" ]; then
	SKU_ALL=`cat $CONFIGDIR/.sku_all | awk '{for(idx=1;idx<=NF;idx++) print $idx;}'`
elif [ -e "target/SKU/$PROJECT/.all" ]; then
	SKU_ALL=`cat target/SKU/$PROJECT/.all | awk '{for(idx=1;idx<=NF;idx++) print $idx;}'`
else
	SKU_ALL=$SKU
fi

echo "Target SKU: $SKU"
rm -f $CONFIGDIR/.sku
echo "$SKU">$CONFIGDIR/.sku
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.sku
fi

echo "All SKUs:"
echo $SKU_ALL | awk '{for(idx=1;idx<=NF;idx++) { printf "- %s\n",$idx;}}'
rm -f $CONFIGDIR/.sku_all
echo "$SKU_ALL">$CONFIGDIR/.sku_all
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.sku_all
fi


# Target Makefile #
if [ ! -n "$3" ]; then
	if [ -e "$CONFIGDIR/.target$SYSTEM_SUFFIX" ]; then
		TARGET=`cat $CONFIGDIR/.target$SYSTEM_SUFFIX | awk '{print $1}'`
	elif [ -e "target/SKU/$PROJECT/.target$SYSTEM_SUFFIX" ]; then
		TARGET=`cat target/SKU/$PROJECT/.target$SYSTEM_SUFFIX | awk '{print $1}'`
	else
		if [ "$WINDIR" != "" ]; then
			TARGET="`cat $DEFAULTDIR/windows.target`"
		else
			TARGET="`cat $DEFAULTDIR/linux.target`"
		fi
	fi
	
	while true; do
		echo -n "Target Makefile [$TARGET]: "
		read answer
		if [ "$answer" != "" ]; then
			# Answer Given #
			if [ -e "$answer" ]; then
				TARGET="$answer"
				break
			else
				echo "Error! $answer not found!"
				#exit -1
			fi
		else
			# No Answer Given (Just pushed enter) #
			if [ -e "$TARGET" ]; then
				break
			else
				echo "Error! $TARGET not found!"
				#exit -1
			fi
		fi
	done
else
	if [ -e "$3" ]; then
		TARGET="$3"
	else
		echo "Error! $3 not found!"
		exit -1
	fi
fi

echo "Target Makefile: $TARGET"
rm -f $CONFIGDIR/.target$SYSTEM_SUFFIX
echo "$TARGET">$CONFIGDIR/.target$SYSTEM_SUFFIX
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.target$SYSTEM_SUFFIX
fi

# End #
echo "Done."
exit 0
