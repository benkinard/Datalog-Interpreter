#include "PlainParameter.h"

PlainParameter::PlainParameter(std::string value) {
    idString = value;
}

std::string PlainParameter::toString() {
    return idString;
}

