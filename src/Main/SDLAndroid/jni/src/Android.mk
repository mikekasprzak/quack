LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main
SDL_PATH := ../SDL2

# Load our generated list of things #
include ../../../output/sku_client-makefile_android/Android.mk

DEFINES			:=	$(addprefix -D,$(DEFINES))

LOCAL_CFLAGS	:= $(DEFINES) $(CFLAGS)
LOCAL_CPPFLAGS	:= $(DEFINES) $(CPPFLAGS)
LOCAL_LDFLAGS	:= $(LDFLAGS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(addprefix ../../../,$(INCLUDES))

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	$(addprefix ../../../../../,$(CODE_FILES))

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := $(LIBRARIES) -llog

# -llog - Needed for __android_log_print

include $(BUILD_SHARED_LIBRARY)
