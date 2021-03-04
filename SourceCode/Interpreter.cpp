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
    for (unsigned int k = 0; k < program->facts.size(); k++) {
        std::string name = program->facts.at(k)->id;
        std::vector<std::string> values;
        for (unsigned int m = 0; m < program->facts.at(k)->parameters.size(); m++) {
            values.push_back(program->facts.at(k)->parameters.at(m)->toString());
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

void Interpreter::evaluateQueries() {
    for (unsigned int i = 0; i < program->queries.size(); i++) {
        Relation* query = nullptr;
        query = evaluatePredicate(program->queries.at(i));
        // std::cout << [INSERT QUERY HERE] << "? " << [YES OR NO(n)] << std::endl;
        query->toString();
        delete query;
        query = nullptr;
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate* p) {
    std::string name = p->id;
    Relation* finalRel = nullptr;
    std::map<std::string, int> variables;
    std::vector<std::string> variableOrder;
    for (std::map<std::string, Relation*>::iterator itr = database->relations.begin();
         itr != database->relations.end(); itr++) {
             if (itr->first == name) {
                 finalRel = itr->second;
                 break;
             }
         }
    for (unsigned int i = 0; i < p->parameters.size(); i++) {
        if (p->parameters.at(i)->isConstant) {  // This is a constant
            // finalRel = finalRel->Select(i, p->parameter.at(i)->toString());
        } else {    // This is a variable
            std::map<std::string, int>::iterator varItr = variables.find(p->parameters.at(i)->toString());
            if (varItr != variables.end()) {    // We've seen this variable before
                // finalRel = finalRel->Select(varItr->second, i);
            } else {    // We haven't seen this variable before
                variables.insert(std::pair<std::string, int> (p->parameters.at(i)->toString(), i));
                variableOrder.push_back(p->parameters.at(i)->toString());
            }
        }
    }
    
    // finalRel = finalRel->Project();
    // finalRel = finalRel->Rename();
    return finalRel;
}