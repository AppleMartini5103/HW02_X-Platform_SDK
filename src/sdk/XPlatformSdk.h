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

// 로그 레벨
typedef enum {
    XPLATFORM_LOG_LEVEL_TRACE = 0,
    XPLATFORM_LOG_LEVEL_DEBUG = 1,
    XPLATFORM_LOG_LEVEL_INFO = 2,
    XPLATFORM_LOG_LEVEL_WARN = 3,
    XPLATFORM_LOG_LEVEL_ERROR = 4,
    XPLATFORM_LOG_LEVEL_CRITICAL = 5,
    XPLATFORM_LOG_LEVEL_OFF = 6,
} xplatform_log_level_t;

// SDK 버전 정보
typedef struct {
    int         major;
    int         minor;
    int         patch;
    const char* name;
    const char* manufacturer;
} xplatform_sdk_version_t;

// API - SDK 초기화 (최초 1회 호출)
XPLATFORM_API void init(xplatform_log_level_t logLevel = XPLATFORM_LOG_LEVEL_TRACE);

// API - SDK 종료 (프로그램 종료 전 1회 호출)
XPLATFORM_API void shutdown();

// API - 카메라 연결
XPLATFORM_API bool connect(const char* ip, int port);

// API - 카메라 연결 해제
XPLATFORM_API void disconnect();

// API - SDK 버전 조회
XPLATFORM_API void getVersion(xplatform_sdk_version_t* version);

#ifdef __cplusplus
} /* extern "C" */
#endif
