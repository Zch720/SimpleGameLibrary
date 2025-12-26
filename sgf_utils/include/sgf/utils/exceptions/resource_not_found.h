#pragma once

#include <exception>
#include <string>

namespace sgf_core {
    class ResourceNotFound : public std::exception {
        public:
            ResourceNotFound(const std::string & message);

            virtual const char* what() const noexcept override;

        private:
            std::string message;
    };
}