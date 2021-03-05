#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    Interpreter(DatalogProgram* input);
    ~Interpreter();
    void evaluateQueries();
private:
    Relation* evaluatePredicate(const Predicate* p);
    DatalogProgram* program;
    Database* database;
};

#endif