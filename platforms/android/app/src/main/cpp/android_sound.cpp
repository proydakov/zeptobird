#include "android_sound.h"

#include <jni.h>
#include <android_native_app_glue.h>

android_sound::android_sound(android_app *app) :
    m_app(app)
{
}

android_sound::~android_sound()
{
    m_app = nullptr;
}

void android_sound::play_music(const std::string& music)
{
    JNIEnv* jni;
    m_app->activity->vm->AttachCurrentThread(&jni, NULL);

    jclass clazz = jni->GetObjectClass(m_app->activity->clazz);
    jmethodID method = jni->GetMethodID(clazz, "playMusic", "(Ljava/lang/String;)V");
    jstring jstr = jni->NewStringUTF(music.c_str());
    jni->CallVoidMethod(m_app->activity->clazz, method, jstr);
    jni->DeleteLocalRef(jstr);

    m_app->activity->vm->DetachCurrentThread();
}

void android_sound::stop_music()
{
    JNIEnv* jni;
    m_app->activity->vm->AttachCurrentThread(&jni, NULL);

    jclass clazz = jni->GetObjectClass(m_app->activity->clazz);
    jmethodID method = jni->GetMethodID(clazz, "stopMusic", "()V");
    jni->CallVoidMethod(m_app->activity->clazz, method);

    m_app->activity->vm->DetachCurrentThread();
}

void android_sound::play_sound(const std::string& sound)
{
    JNIEnv* jni;
    m_app->activity->vm->AttachCurrentThread(&jni, NULL);

    jclass clazz = jni->GetObjectClass(m_app->activity->clazz);
    jmethodID method = jni->GetMethodID(clazz, "playSound", "(Ljava/lang/String;)V");
    jstring jstr = jni->NewStringUTF(sound.c_str());
    jni->CallVoidMethod(m_app->activity->clazz, method, jstr);
    jni->DeleteLocalRef(jstr);

    m_app->activity->vm->DetachCurrentThread();
}
