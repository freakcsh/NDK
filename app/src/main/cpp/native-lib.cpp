#include <jni.h>
#include <string>
#include "stdlib.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_freak_ndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
//调用类属性
extern "C"
JNIEXPORT jstring JNICALL
Java_com_freak_ndk_MainActivity_stringFromMyJNI(JNIEnv *env, jobject instance) {

    // TODO
    //jobject代表的是什么？ 代表的调用的类对象 首先获取jclass
    jclass _jclass = env->GetObjectClass(instance);
    //访问类对象属性 要获取FieldID
    //jclass clazz, const char* name, const char* sig
    jfieldID _jfielID = env->GetFieldID(_jclass, "name", "Ljava/lang/String;");
    //读取属性
    jstring _jstring1 = (jstring) env->GetObjectField(instance, _jfielID);
//    printf("%#x\n", _jstring1);
    //如何去转化成java的string类型
    char *result = (char *) env->GetStringUTFChars(_jstring1, NULL);
//    char text[20] = "success";
//    char *string=strcat(result,text);

    return env->NewStringUTF(result);
}
//调用类方法
extern "C"
JNIEXPORT jstring JNICALL
Java_com_freak_ndk_MainActivity_getMes(JNIEnv *env, jobject instance) {

    // TODO
    //jobject代表的是什么？ 代表的调用的类对象 首先获取jclass
    jclass _jclass = env->GetObjectClass(instance);
    //调用类对象中的java方法
    //jclass clazz, const char* name, const char* sig
    //获取对象的方法签名
    jmethodID _jmethodID = env->GetMethodID(_jclass, "getName", "()Ljava/lang/String;");
    //调用类对象的方法
    jstring jstring1 = (jstring) env->CallObjectMethod(instance, _jmethodID);
    //如何去转化成java的string类型
    char *result = (char *) env->GetStringUTFChars(jstring1, NULL);


    return env->NewStringUTF(result);
}

/**
 * 首先将__lhs强制声明为指向整数的指针，读取指针对应的整数
 * (int *) __lhs是将__lhs强制声明为指向整数的指针，*(int *) __lhs是读取指针对应的整数
 * @param __lhs
 * @param __rhs
 * @return
 */
int compare(const void *__lhs, const void *__rhs) {
    return (*(int *) __lhs) - *(int *) __rhs;
}
//调用java数组
extern "C"
JNIEXPORT void JNICALL
Java_com_freak_ndk_MainActivity_getArray(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = env->GetIntArrayElements(array_, NULL);

    // TODO
    //获取数组长度
    int _len = env->GetArrayLength(array_);
    //void* __base, size_t __nmemb, size_t __size, int (*__comparator)(const void* __lhs, const void* __rhs));
   //排序 此方法在stdlib.h中
    qsort(array, _len, sizeof(int), compare);


    env->ReleaseIntArrayElements(array_, array, 0);
}
//调用引用
extern "C"
JNIEXPORT void JNICALL
Java_com_freak_ndk_MainActivity_getLocalReference(JNIEnv *env, jobject instance) {

    // TODO
    //模拟循环
    for (int i = 0; i < 100; ++i) {
        jclass _jclass1=env->FindClass("java/util/Date");
      jobject  _jobject1= env->NewObject(_jclass1,env->GetMethodID(_jclass1,"<init>","()v"));
        //对象操作--删除对象
        env->DeleteLocalRef(_jobject1);

    }

}