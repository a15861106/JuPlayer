LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

MY_ALL_DIRS := $(LOCAL_PATH)/ \

LOCAL_MODULE    := JuPlayer
LOCAL_SRC_FILES := JuPlayer.cpp \
Decoder.cpp \
H264Decoder.cpp \

LOCAL_C_INCLUDES := $(MY_ALL_DIRS)
LOCAL_LDLIBS :=  -llog -ljnigraphics -lz -landroid
LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS -std=c++11
LOCAL_SHARED_LIBRARIES := libavformat libswresample libavcodec libswscale libavutil
APP_OPTIM := debug

include $(BUILD_SHARED_LIBRARY)

$(call import-module, ffmpeg-2.8/android/arm)
