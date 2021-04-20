#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
public:
    Interpreter(DatalogProgram* input);
    ~Interpreter();
    void evaluateRules();
    void evaluateQueries();
private:
    bool evaluateRule(const Rule* r);
    Relation* evaluatePredicate(const Predicate* p);
    DatalogProgram* program;
    Database* database;
};

#endif