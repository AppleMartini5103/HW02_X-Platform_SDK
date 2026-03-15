#pragma once

#ifdef _WIN32
  #ifdef XPLATFORM_SDK_EXPORTS
    #define XPLATFORM_API __declspec(dllexport)
  #else
    #define XPLATFORM_API __declspec(dllimport)
  #endif
#elif defined(__ANDROID__)
  #define XPLATFORM_API __attribute__((visibility("default")))
#elif defined(__linux__)
    #define XPLATFORM_API __attribute__((visibility("default")))
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if TARGET_OS_IPHONE
    // iOS (iPhone, iPad)
    #define XPLATFORM_API __attribute__((visibility("default")))
  #else
    // macOS
    #define XPLATFORM_API __attribute__((visibility("default")))
  #endif
#endif

#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

// SDK 버전 정보
typedef struct {
    int         major;
    int         minor;
    int         patch;
    const char* name;
    const char* manufacturer;
} xplatform_sdk_version_t;

// API - SDK 버전 조회
XPLATFORM_API void getVersion(xplatform_sdk_version_t* version);

// API - 카메라 연결
XPLATFORM_API bool connect(const char* ip, int port);

// API - 카메라 연결 해제
XPLATFORM_API void disconnect();

#ifdef __cplusplus
} /* extern "C" */
#endif
