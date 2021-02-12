#ifndef PLAINPARAMETER_H
#define PLAINPARAMETER_H
#include <string>
#include "Parameter.h"

class PlainParameter : public Parameter {
public:
    PlainParameter(std::string value);
    ~PlainParameter() = default;
    std::string toString();

private:
    std::string idString;
};


#endif
