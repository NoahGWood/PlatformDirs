#pragma once
#include <filesystem>
#include <string_view>
#include <cstdlib>

#if defined(__ANDROID__)
#include <jni.h>
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#endif
#endif

namespace std::filesystem
{
#if defined(__ANDROID__)
    inline static JNIEnv* g_env = nullptr;
    inline static jobject g_ctx = nullptr;
    inline void init(JNIEnv* env, jobject context) { g_env = env; g_ctx = context; }
#endif

    inline path get_app_dir(std::string_view app_name) {
#if defined(_WIN32)
        return path(getenv("APPDATA")) / app_name;
#elif defined(__APPLE__)  && !TARGET_OS_IPHONE
        return path(getenv("HOME")) / "Library/Application Support" / app_name;
#elif defined(__ANDROID__)
    if (!g_env || !g_ctx) return "/data/local/tmp/" / app_name; // fallback
    jclass cls = g_env->GetObjectClass(g_ctx);
    jmethodID mid = g_env->GetMethodID(cls, "getFilesDir", "()Ljava/io/File;");
    jobject fileObj = g_env->CallObjectMethod(g_ctx, mid);
    jclass fileCls = g_env->GetObjectClass(fileObj);
    jmethodID getPath = g_env->GetMethodID(fileCls, "getPath", "()Ljava/lang/String;");
    jstring pathStr = (jstring)g_env->CallObjectMethod(fileObj, getPath);
    const char* path = g_env->GetStringUTFChars(pathStr, nullptr);
    auto result = std::filesystem::path(path) / app_name;
    g_env->ReleaseStringUTFChars(pathStr, path);
    return result;
#elif defined(__APPLE__) && TARGET_OS_IPHONE
    @autoreleasepool {
        NSArray* paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
        NSString* path = [paths firstObject];
        return std::filesystem::path([path UTF8String]) / app_name;
    }
#else
    const char* xdg = std::getenv("XDG_CONFIG_HOME");
    const char* home = std::getenv("HOME");
    return xdg ? std::filesystem::path(xdg) / app_name : std::filesystem::path(home) / ".config" / app_name;
#endif
    }

    inline std::filesystem::path get_config_dir(std::string_view app_name) {
        return get_app_dir(app_name) / "config";
    }

    inline std::filesystem::path get_cache_dir(std::string_view app_name) {
        return get_app_dir(app_name) / "cache";
    }

    inline std::filesystem::path get_data_dir(std::string_view app_name) {
        return get_app_dir(app_name) / "data";
    }

    inline std::filesystem::path get_log_dir(std::string_view app_name) {
        return get_app_dir(app_name) / "logs";
    }

    inline std::filesystem::path get_temp_dir() {
        return std::filesystem::temp_directory_path();
    }

} // namespace std::filesystem
