#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

class Parameter {
public:
    Parameter()= default;
    virtual ~Parameter() = default;
    virtual std::string toString() = 0;
};

#endif
