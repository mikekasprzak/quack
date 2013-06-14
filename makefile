# - ------------------------------------------------------------------------ - #
# make other target=clean
# - ------------------------------------------------------------------------ - #
BUILD_MAKEFILE		:=	Target/makefile
# - ------------------------------------------------------------------------ - #
__PROJECT_FILE__	:=	Config/.project
__SKU_FILE__		:=	Config/.sku
__SKU_ALL_FILE__	:=	Config/.sku_all
# - ------------------------------------------------------------------------ - #
PROJECT_FILE		=	$(shell cat $(__PROJECT_FILE__))
SKU_FILE			=	$(shell cat $(__SKU_FILE__))
SKU_ALL_FILE		=	$(shell cat $(__SKU_ALL_FILE__))
# - ------------------------------------------------------------------------ - #
ifdef NUMBER_OF_PROCESSORS
NUM_PROCESSORS		:=	$(NUMBER_OF_PROCESSORS)
else # NUMBER_OF_PROCESSORS #
NUM_PROCESSORS		:=	$(shell nproc)
endif # NUMBER_OF_PROCESSORS #
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
.PHONY: default run clean cleanmain info all cache startcache
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
# MinGW HACK -- Blank out the Number of processors (so -j without args) #
NUM_PROCESSORS 		:=
# - ------------------------------------------------------------------------ - #
default:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS)
run clean cleanmain info files upload package install cache startcache:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS) $@
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
all: $(addprefix obj/,$(SKU_ALL_FILE))
# - ------------------------------------------------------------------------ - #
other: $(addprefix obj/,$(filter-out $(notdir $(SKU_FILE)),$(SKU_ALL_FILE)))
# - ------------------------------------------------------------------------ - #
obj/%:
	$(MAKE) -f $(BUILD_MAKEFILE) -j SKU_FILE=SKU/$(PROJECT_FILE)/$* $(target) $(action)
# - ------------------------------------------------------------------------ - #
