/*
 * jni_log.h
 *  简化Log打印
 *  Created on: Jan 6, 2015
 *      Author: Juwan
 */

#ifndef JNI_LOG_H_
#define JNI_LOG_H_

#include <android/log.h>
#include <jni.h>

#define LOG_TAG "JNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGW(...)	__android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#endif /* JNI_LOG_H_ */
