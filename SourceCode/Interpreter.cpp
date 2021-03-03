#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram* input) : program(input), database(new Database()) {
    // Add empty relations with their name and header
    for (unsigned int i = 0; i < program->schemes.size(); i++) {
        std::string name = program->schemes.at(i)->id;
        std::vector<std::string> columns;
        for (unsigned int j = 0; j < program->schemes.at(i)->parameters.size(); j++) {
            columns.push_back(program->schemes.at(i)->parameters.at(j)->toString());
        }
        auto header = new Header(columns);
        auto relation = new Relation(name, header);
        database->AddRelation(relation);
    }
    
    // Add tuples to the previously created relations
    for (unsigned int i = 0; i < program->facts.size(); i++) {
        std::string name = program->facts.at(i)->id;
        std::vector<std::string> values;
        for (unsigned int j = 0; j < program->facts.at(i)->parameters.size(); j++) {
            values.push_back(program->facts.at(i)->parameters.at(j)->toString());
        }
        Tuple tuple(values);
        for (std::map<std::string, Relation*>::iterator itr = database->relations.begin();
             itr != database->relations.end(); itr++) {
            if (name == itr->first) {
                itr->second->AddTuple(tuple);
                break;
            }
        }
    }

    // REMOVE LATER
    database->PrintRelations();
}

Interpreter::~Interpreter() {
    delete program;
    program = nullptr;
    delete database;
    database = nullptr;
}