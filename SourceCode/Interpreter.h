#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    Interpreter(DatalogProgram* input);
    ~Interpreter();
private:
    DatalogProgram* program;
    Database* database;
};

#endif