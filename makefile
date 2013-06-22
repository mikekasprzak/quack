# - ------------------------------------------------------------------------ - #
# make other target=clean
# - ------------------------------------------------------------------------ - #
BUILD_MAKEFILE		:=	target/makefile
# - ------------------------------------------------------------------------ - #
__PROJECT_FILE__	:=	config/.project
__SKU_FILE__		:=	config/.sku
__SKU_ALL_FILE__	:=	config/.sku_all
# - ------------------------------------------------------------------------ - #
PROJECT_FILE		=	$(shell cat $(__PROJECT_FILE__))
SKU_FILE			=	$(shell cat $(__SKU_FILE__))
SKU_ALL_FILE		=	$(shell cat $(__SKU_ALL_FILE__))
# - ------------------------------------------------------------------------ - #
# MinGW HACK -- Blank out the Number of processors (so -j without args) #
ifdef WINDIR
NUM_PROCESSORS		:=	$(J)
else # WINDIR #
ifdef J
NUM_PROCESSORS		:=	$(J)
else # J #
NUM_PROCESSORS		:=	$(shell nproc)
endif # J #
endif # WINDIR #
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
.PHONY: default run clean cleanmain info all cache startcache
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
default:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS)
run debug gdebug clean cleanmain info files upload package install cache startcache:
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
