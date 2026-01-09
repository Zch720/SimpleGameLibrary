#pragma once

#include <memory>
#include "./logger.h"

namespace sgf_core {
    class SpdlogAdapter: public Logger {
    public:
        SpdlogAdapter();
        ~SpdlogAdapter();

        void consoleLevel(LoggerLevel level) override;
        void fileLevel(LoggerLevel level) override;

        void info(const std::string & message) override;
        void warn(const std::string & message) override;
        void error(const std::string & message) override;
        void debug(const std::string & message) override;
    
    private:
        struct AdapterImpl;

        std::unique_ptr<AdapterImpl> impl;
    };
}
