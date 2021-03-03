#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    Interpreter(DatalogProgram* input);
    ~Interpreter();
    void evaluateQueries();
    Relation* evaluatePredicate(const Predicate* p);
private:
    DatalogProgram* program;
    Database* database;
};

#endif