#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "BitmapNdkDemo"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_treech_bitmap_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGI("hello num:%d,text:%s", 10, "Bitmap");
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_treech_bitmap_ndkdemo_MainActivity_passBitmap(
        JNIEnv *env,
        jobject /* this */,
        jobject bitmap) {
    if (NULL == bitmap) {
        LOGE("bitmap is null!");
        return;
    }
    AndroidBitmapInfo info; // create a AndroidBitmapInfo
    int result;
    // 获取图片信息
    result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_getInfo failed, result: %d", result);
        return;
    }
    LOGI("bitmap width: %d, height: %d, format: %d, stride: %d", info.width, info.height,
         info.format, info.stride);
    // 获取像素信息
    unsigned char *addrPtr;
    result = AndroidBitmap_lockPixels(env, bitmap, reinterpret_cast<void **>(&addrPtr));
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_lockPixels failed, result: %d", result);
        return;
    }
    // 执行图片操作的逻辑
    int length = info.stride * info.height;
    for (int i = 0; i < length; ++i) {
        LOGD("value: %x", addrPtr[i]);
    }
    // 像素信息不再使用后需要解除锁定
    result = AndroidBitmap_unlockPixels(env, bitmap);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_unlockPixels failed, result: %d", result);
    }
}