#ifdef SWIGJAVA
%insert("runtime") %{
#ifdef __ANDROID__
#define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
#define SWIG_JAVA_ATTACH_CURRENT_THREAD_AS_DAEMON
#endif
%}
#endif

%module glyph
%{
#include <GlyphParser.h>
%}

%include <GlyphParser.h>

#ifdef SWIGJAVA
%{
#ifdef __ANDROID__
#include <android/log.h>
struct TmpLogFunc {
    const char* name;
    TmpLogFunc(const char* name) : name(name) {
        __android_log_print(ANDROID_LOG_VERBOSE,"vgstack","%s enter",name);
    }
    ~TmpLogFunc() {
        __android_log_print(ANDROID_LOG_VERBOSE,"vgstack","%s exit",name);
    }
};
#endif

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* /*ajvm*/, void* /*reserved*/) {
    return JNI_VERSION_1_6;
}
%}
#endif
