#pragma once

#include <string>
#include <fmt/core.h>
#include "./logger.h"

namespace sgf_core {
    namespace log {
        void init();
        void drop();

        void consoleLevel(LoggerLevel level);
        void fileLevel(LoggerLevel level);

        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
        void debug(std::string msg);
    }
}

#define SGF_LOG_LEVEL_NONE  sgf_core::LoggerLevel::None
#define SGF_LOG_LEVEL_INFO  sgf_core::LoggerLevel::Info
#define SGF_LOG_LEVEL_WARN  sgf_core::LoggerLevel::Warn
#define SGF_LOG_LEVEL_ERROR sgf_core::LoggerLevel::Error
#define SGF_LOG_LEVEL_DEBUG sgf_core::LoggerLevel::Debug

#ifdef SGF_LOG
    #define SGF_LOG_INIT() sgf_core::log::init()
    #define SGF_LOG_DROP() sgf_core::log::drop()

    #define SGF_LOG_CONSOLE(level) sgf_core::log::consoleLevel(level)
    #define SGF_LOG_FILE(level) sgf_core::log::fileLevel(level)

    #define SGF_LOG_INFO(...) sgf_core::log::info(fmt::format(__VA_ARGS__))
    #define SGF_LOG_WARN(...) sgf_core::log::warn(fmt::format(__VA_ARGS__))
    #define SGF_LOG_ERROR(...) sgf_core::log::error(fmt::format(__VA_ARGS__))

    #ifdef SGF_DEBUG_LOG
        #define SGF_LOG_DEBUG(...) sgf_core::log::debug(fmt::format(__VA_ARGS__))
    #else
        #define SGF_LOG_DEBUG(...) ((void)0)
    #endif
#else
    #define SGF_LOG_INIT() ((void)0)
    #define SGF_LOG_DROP() ((void)0)
    #define SGF_LOG_CONSOLE(level) ((void)0)
    #define SGF_LOG_FILE(level) ((void)0)
    #define SGF_LOG_INFO(...) ((void)0)
    #define SGF_LOG_WARN(...) ((void)0)
    #define SGF_LOG_ERROR(...) ((void)0)
    #define SGF_LOG_DEBUG(...) ((void)0)
#endif
