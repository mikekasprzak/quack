LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main
SDL_PATH := ../SDL2

# Load our generated list of things #
include ../../output/sku_client-makefile_android/Quack.so.mk

_FLAGS			:=	$(addprefix -D,$(DEFINES)) -fexceptions

LOCAL_CFLAGS	:= $(_FLAGS)
LOCAL_CPPFLAGS	:= $(_FLAGS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(addprefix ../../,$(INCLUDES))

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	$(addprefix ../../../../,$(CODE_FILES))

#	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
#	$(SDL_PATH)/test/testgles.c \
#	$(SDL_PATH)/src/test/SDL_test_common.c

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv2 -llog
#-lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
