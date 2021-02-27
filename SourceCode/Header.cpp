#include "Header.h"

Header::Header(std::vector<std::string> schema) {
    attributes = schema;
}

std::vector<std::string> Header::getHeader() const {
    return attributes;
}