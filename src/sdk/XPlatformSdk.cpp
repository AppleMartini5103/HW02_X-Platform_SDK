#include "XPlatformSdk.h"

#include <cstdio>
#include <memory>
#include <mutex>
#include <string>

#include "info/version.h"

// 네트워크 및 서비스 (전역 싱글톤 디자인 패턴)
namespace {
    std::mutex _mutex;

    // 연결 상태
    bool        _connected = false;
    std::string _ip;
    int         _port = 0;

} // namespace

void getVersion(xplatform_sdk_version_t* version) {
    if (!version) {
        return;
    }

    version->major        = XPLATFORM_SDK_VERSION_MAJOR;
    version->minor        = XPLATFORM_SDK_VERSION_MINOR;
    version->patch        = XPLATFORM_SDK_VERSION_PATCH;
    version->name         = XPLATFORM_SDK_NAME;
    version->manufacturer = XPLATFORM_SDK_MANUFACTURER;

    printf("[Sdk] get version: %s v%d.%d.%d (%s)\n",
        version->name,
        version->major, version->minor, version->patch,
        version->manufacturer);
}

bool connect(const char* ip, int port) {
    std::lock_guard<std::mutex> lock(_mutex);

    printf("[Sdk] connect: ip=(%s) port=(%d)\n", ip, port);

    // 이미 연결된 경우 먼저 정리
    if (_connected) {
        printf("[Sdk] connect: already connected, disconnecting first\n");
        _connected = false;
    }

    _ip   = ip;
    _port = port;

    // TODO: 실제 RTSP 연결 구현
    //

    _connected = true;

    printf("[Sdk] connect: OK\n");
    return true;
}

void disconnect() {
    std::lock_guard<std::mutex> lock(_mutex);

    printf("[Sdk] disconnect\n");

    if (!_connected) {
        printf("[Sdk] disconnect: not connected\n");
        return;
    }

    // TODO: 실제 RTSP 연결 해제 구현
    //
    
    _connected = false;
    _ip.clear();
    _port = 0;

    printf("[Sdk] disconnect: OK\n");
}
