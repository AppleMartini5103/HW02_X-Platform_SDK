#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#define LOG_TRACE(...)  spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...)  spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...)  spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)  spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

namespace Logger {

    // 로거 초기화 - 콘솔 + 파일 동시 출력
    // logPath: 로그 파일 경로 (예: "logs/sdk.log")
    // maxFileSize: 파일 최대 크기 (바이트, 기본 5MB)
    // maxFiles: 최대 보관 파일 수 (기본 3개)
    inline void init(spdlog::level::level_enum logLevel = spdlog::level::trace,
                     const std::string& logPath         = "logs/sdk.log",
                     size_t maxFileSize                  = 1024 * 1024 * 5,
                     int    maxFiles                     = 3)
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink    = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logPath, maxFileSize, maxFiles
        );

        auto logger = std::make_shared<spdlog::logger>(
            "sdk", spdlog::sinks_init_list{console_sink, file_sink}
        );

        spdlog::set_default_logger(logger);
        spdlog::set_level(logLevel);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    }

    // 로거 종료 - 버퍼 flush 후 정리
    inline void shutdown() {
        spdlog::shutdown();
    }

} // namespace Logger
