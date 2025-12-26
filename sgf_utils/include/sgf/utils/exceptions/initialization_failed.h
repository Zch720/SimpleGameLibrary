#pragma once

#include <exception>
#include <string>

namespace sgf_core {
    class InitializationFailed : public std::exception {
        public:
            InitializationFailed(const std::string & message);

            virtual const char* what() const noexcept override;

        private:
            std::string message;
    };
}
