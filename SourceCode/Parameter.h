#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

class Parameter {
    friend class Interpreter;
public:
    Parameter()= default;
    virtual ~Parameter() = default;
    virtual std::string toString() = 0;
protected:
    bool isConstant;
};

#endif
