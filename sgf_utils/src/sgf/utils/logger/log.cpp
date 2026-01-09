#include "../../../../include/sgf/utils/logger/log.h"
#include <cstdarg>
#include <memory>
#include "../../../../include/sgf/utils/exceptions/invalid_state.h"
#include "../../../../include/sgf/utils/logger/logger_spdlog_adapter.h"

namespace sgf_core {
    namespace log {
        std::unique_ptr<Logger> logger;

        void init() {
            if (logger != nullptr) {
                throw InvalidState("Logger already initialized");
            }
            logger = std::make_unique<SpdlogAdapter>();
        }

        void drop() {
            logger = nullptr;
        }

        void consoleLevel(LoggerLevel level) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->consoleLevel(level);
        }

        void fileLevel(LoggerLevel level) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->fileLevel(level);
        }

        void info(std::string msg) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->info(msg);
        }

        void warn(std::string msg) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->warn(msg);
        }

        void error(std::string msg) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->error(msg);
        }

        void debug(std::string msg) {
            if (logger == nullptr) {
                throw InvalidState("Logger not initialized yet");
            }
            logger->debug(msg);
        }
    }
}
