#pragma once

#include <exception>
#include <string>

namespace sgf_core {
    class InvalidState : public std::exception {
        public:
            InvalidState(const std::string & message);

            virtual const char* what() const noexcept override;

        private:
            std::string message;
    };
}
