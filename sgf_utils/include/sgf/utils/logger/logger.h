#pragma once

#include <string>

namespace sgf_core {
    enum LoggerLevel {
        None,
        Error,
        Warn,
        Info,
        Debug,
    };

    class Logger {
    public:
        virtual ~Logger() = default;
        
        virtual void consoleLevel(LoggerLevel level) = 0;
        virtual void fileLevel(LoggerLevel level) = 0;

        virtual void info(const std::string & message) = 0;
        virtual void warn(const std::string & message) = 0;
        virtual void error(const std::string & message) = 0;
        virtual void debug(const std::string & message) = 0;
    };
}
