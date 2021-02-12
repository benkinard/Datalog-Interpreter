#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <vector>
#include "Parameter.h"

class Expression : public Parameter {
public:
    Expression(std::vector<Parameter*> params, std::string addmult);
    ~Expression();
    std::string toString();

private:
    std::string oper;
    std::vector<Parameter*> bothParameters;
};

#endif
