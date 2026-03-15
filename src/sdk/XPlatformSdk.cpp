#include "XPlatformSdk.h"

#include <memory>
#include <mutex>
#include <string>

#include "info/version.h"
#include "util/log/logger.h"

// 네트워크 및 서비스 (전역 싱글톤 디자인 패턴)
namespace {
    std::mutex _mutex;

    // 연결 상태
    bool _connected = false;
    std::string _ip;
    int _port = 0;

} // namespace

void init() {
    //logger
    Logger::init();

    LOG_INFO("[Sdk] init successed");
}

void shutdown() {
    LOG_INFO("[Sdk] shutdown");

    Logger::shutdown();

    LOG_INFO("[Sdk] shutdown successed");
}

bool connect(const char* ip, int port) {
    std::lock_guard<std::mutex> lock(_mutex);

    LOG_INFO("[Sdk] connect: ip=({}) port=({})", ip, port);

    // 이미 연결된 경우 먼저 정리
    if (_connected) {
        LOG_WARN("[Sdk] connect: already connected, disconnecting first");
        _connected = false;
    }

    _ip = ip;
    _port = port;

    // TODO: 실제 RTSP 연결 구현

    _connected = true;

    LOG_INFO("[Sdk] connect: OK");
    return true;
}

void disconnect() {
    std::lock_guard<std::mutex> lock(_mutex);

    LOG_INFO("[Sdk] disconnect");

    if (!_connected) {
        LOG_WARN("[Sdk] disconnect: not connected");
        return;
    }

    // TODO: 실제 RTSP 연결 해제 구현

    _connected = false;
    _ip.clear();
    _port = 0;

    LOG_INFO("[Sdk] disconnect: OK");
}

void getVersion(xplatform_sdk_version_t* version) {
    if (!version) {
        return;
    }

    version->major = XPLATFORM_SDK_VERSION_MAJOR;
    version->minor = XPLATFORM_SDK_VERSION_MINOR;
    version->patch = XPLATFORM_SDK_VERSION_PATCH;
    version->name = XPLATFORM_SDK_NAME;
    version->manufacturer = XPLATFORM_SDK_MANUFACTURER;

    LOG_INFO("[Sdk] get version: {} v{}.{}.{} ({})",
        version->name,
        version->major, version->minor, version->patch,
        version->manufacturer);
}
