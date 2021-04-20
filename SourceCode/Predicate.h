#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
    friend class Interpreter;
    friend class Graph;
public:
    Predicate() = default;
    ~Predicate();
    void SetID(std::string input);
    void AddParameters(std::vector<Parameter*> newParameters);
    std::string toString();

private:
    std::string id;
    std::vector<Parameter*> parameters;
};

#endif
