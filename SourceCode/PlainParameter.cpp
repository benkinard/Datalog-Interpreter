#include "PlainParameter.h"

PlainParameter::PlainParameter(std::string value, bool constant) {
    idString = value;
    isConstant = constant;
}

std::string PlainParameter::toString() {
    return idString;
}

