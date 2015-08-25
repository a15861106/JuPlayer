//
// Created by Juwan on 8/25/2015.
//

#include "JuPlayer.h"
#include "jni_log.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

extern "C" jstring Java_com_juwan_juplayer_jni_Ffmpeg_init(JNIEnv *env,
                                                    jobject obj) {

    char ffmpeg_version[20] = "";
    sprintf(ffmpeg_version, "%d", avcodec_version());
    LOGE("%d", avcodec_version());
    return env->NewStringUTF(ffmpeg_version);
}

