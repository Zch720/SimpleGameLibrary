#include "../../../../include/sgf/utils/logger/logger_spdlog_adapter.h"
#include "spdlog/common.h"
#include <fmt/core.h>
#include <memory>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace sgf_core {
    class ConsoleSink {
    public:
        ConsoleSink(): _level(LoggerLevel::None) {
        }

        LoggerLevel level() const {
            return _level;
        }
        void level(LoggerLevel level) {
            _level = level;
        }

        void info(const std::string & message) {
            if (LoggerLevel::Info <= _level)
                spdlog::info(message);
        }
        void warn(const std::string & message) {
            if (LoggerLevel::Warn <= _level)
                spdlog::warn(message);
        }
        void error(const std::string & message) {
            if (LoggerLevel::Error <= _level)
                spdlog::error(message);
        }
        void debug(const std::string & message) {
            if (LoggerLevel::Debug <= _level)
            spdlog::debug(message);
        }
    
    private:
        LoggerLevel _level;
    };

    class FileSink {
    public:
        FileSink(): _level(LoggerLevel::None), fileLogger(nullptr) {
            fileLogger = createLogFile();
            fileLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        }
        
        ~FileSink() {
            spdlog::drop("file_logger");
            fileLogger.reset();
        }

        LoggerLevel level() const {
            return _level;
        }
        void level(LoggerLevel level) {
            _level = level;
        }

        void info(const std::string & message) {
            if (LoggerLevel::Info <= _level && fileLogger != nullptr)
                fileLogger->info(message);
        }
        void warn(const std::string & message) {
            if (LoggerLevel::Warn <= _level && fileLogger != nullptr)
                fileLogger->warn(message);
        }
        void error(const std::string & message) {
            if (LoggerLevel::Error <= _level && fileLogger != nullptr)
                fileLogger->error(message);
        }
        void debug(const std::string & message) {
            if (LoggerLevel::Debug <= _level && fileLogger != nullptr)
                fileLogger->debug(message);
        }
    
    private:
        LoggerLevel _level;
        std::shared_ptr<spdlog::logger> fileLogger;

        std::shared_ptr<spdlog::logger> createLogFile() {
            try {
                return spdlog::basic_logger_mt("file_logger", "logs/log.txt");
            } catch (const spdlog::spdlog_ex & ex) {
                spdlog::error(fmt::format("Failed to init logger file, cause: {}", ex.what()));
            }
            return std::shared_ptr<spdlog::logger>(nullptr);
        }
    };

    struct SpdlogAdapter::AdapterImpl {
        ConsoleSink console;
        FileSink file;
    };

    SpdlogAdapter::SpdlogAdapter() {
        impl = std::make_unique<AdapterImpl>();

        spdlog::set_level(spdlog::level::debug);
    }

    SpdlogAdapter::~SpdlogAdapter() = default;

    void SpdlogAdapter::consoleLevel(LoggerLevel level) {
        impl->console.level(level);
    }
    
    void SpdlogAdapter::fileLevel(LoggerLevel level) {
        impl->file.level(level);
    }

    void SpdlogAdapter::info(const std::string & message) {
        impl->console.info(message);
        impl->file.info(message);
    }

    void SpdlogAdapter::warn(const std::string & message) {
        impl->console.warn(message);
        impl->file.warn(message);
    }

    void SpdlogAdapter::error(const std::string & message) {
        impl->console.error(message);
        impl->file.error(message);
    }
    
    void SpdlogAdapter::debug(const std::string & message) {
        impl->console.debug(message);
        impl->file.debug(message);
    }
}
