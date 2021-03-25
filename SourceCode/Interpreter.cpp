#include "Interpreter.h"
#include <iostream>
#include <list>

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
}

Interpreter::~Interpreter() {
    delete program;
    program = nullptr;
    delete database;
    database = nullptr;
}

void Interpreter::evaluateRules() {
    std::cout << "Rule Evaluation" << std::endl;
    bool dbUpdated = true;
    int rulePasses = 0;
    // Fixed-Point Algorithm
    while (dbUpdated) {
        dbUpdated = false;
        rulePasses++;
        // Loop through each rule in the DatalogProgram
        for (unsigned int i = 0; i < program->rules.size(); i++) {
            std::cout << program->rules.at(i)->toString() << "." << std::endl;
            if (evaluateRule(program->rules.at(i))) {
                dbUpdated = true;
            }
        }
    }
    std::cout << std::endl << "Schemes populated after " << rulePasses << " passes through the Rules.";
    std::cout << std::endl << std::endl;
}

bool Interpreter::evaluateRule(const Rule* r) {
    // *********************** Evaluate Predicates ***********************************
    // Create a list to store the relations that result from each body predicate
    std::list<Relation*> resultingRelations;
    // Loop through each body predicate, evaluate it, and store the relation in the list
    for (unsigned int i = 0; i < r->predicates.size(); i++) {
        resultingRelations.push_back(evaluatePredicate(r->predicates.at(i)));
    }

    // *************************** Join Relations *************************************
    // Perform n-1 joins for the n relations in the list
    Relation* joinRel = resultingRelations.front();
    resultingRelations.pop_front();
    while (!resultingRelations.empty()) {
        Relation* tempRel = joinRel->Join(resultingRelations.front());
        delete joinRel;
        joinRel = tempRel;
        tempRel = resultingRelations.front();
        delete tempRel;
        resultingRelations.pop_front();
    }

    // ********************** Project Head Predicate Columns **************************
    // Find the column positions for the appropriate columns in the head predicate
    std::vector<int> projCols;
    for (unsigned int j = 0; j < r->headPredicate->parameters.size(); j++) {
        for (unsigned int k = 0; k < joinRel->getHeader()->getHeader().size(); k++) {
            if (r->headPredicate->parameters.at(j)->toString() == joinRel->getHeader()->getHeader().at(k)) {
                projCols.push_back(k);
                break;
            }
        }
    }
    // Project the columns of the head predicate using the vector created above
    Relation* projRel = joinRel->Project(projCols);
    delete joinRel;

    // ************************ Rename Header to Match Database ***********************
    // Create vector with appropriate values to initialize the new Header with
    std::vector<std::string> dbAttributes;
    for (std::map<std::string, Relation*>::iterator itr = database->relations.begin();
        itr != database->relations.end(); itr++) {
            if (itr->first == r->headPredicate->id) {
                dbAttributes = itr->second->getHeader()->getHeader();
                break;
            }
    }
    // Create new Header* object to pass in to Rename method of projRel
    auto newHeader = new Header(dbAttributes);
    // Pass in new Header to Rename and store returning Relation
    Relation* renameRel = projRel->Rename(newHeader);
    delete projRel;

    // ********************** Union with Relation in Database *************************
    bool tuplesAdded = false;
    for (std::map<std::string, Relation*>::iterator itr = database->relations.begin();
        itr != database->relations.end(); itr++) {
            if (itr->first == r->headPredicate->id) {
                tuplesAdded = itr->second->UnionOp(renameRel);
                delete renameRel;
                break;
            }
    }
    return tuplesAdded;
}

void Interpreter::evaluateQueries() {
    std::cout << "Query Evaluation" << std::endl;
    // Loop through each query in the DatalogProgram
    for (unsigned int i = 0; i < program->queries.size(); i++) {
        // Pass first query to evaluatePredicate and store result in a Relation*
        Relation* query = nullptr;
        query = evaluatePredicate(program->queries.at(i));
        // Print to screen the query from the DatalogProgram
        std::cout << program->queries.at(i)->toString() << "? ";
        // If the relation returned from evaluating the query is empty
        //      output "No" and move on to next query
        // If it is not empty, output "Yes(n)" where n is the # of tuples
        //      that matched the query
        if (query->getTuples().empty()) {   // Relation IS empty
            std::cout << "No" << std::endl;
        } else {    // Relation IS NOT empty
            std::cout << "Yes(" << query->getTuples().size() << ")" << std::endl;
            // If only constants were present in the query, we are done with output
            // If variables were present in the query, we want to print those out too
            bool varPresent = false;
            Relation* dbRel = database->relations.find(query->getName())->second;
            for (unsigned int j = 0; j < query->getHeader()->getHeader().size(); j++) {
                if (query->getHeader()->getHeader().at(j) != dbRel->getHeader()->getHeader().at(j)) {
                    varPresent = true;
                    break;
                }
            }
            if (varPresent) {
                std::cout << query->toString();
            }
        }
        delete query;
        query = nullptr;
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate* p) {
    // Find the relation in the DataBase that matches the name of the current query
    std::string name = p->id;
    Relation* dbRel = nullptr;
    std::map<std::string, int> variables;
    std::vector<std::string> varNames;
    for (std::map<std::string, Relation*>::iterator itr = database->relations.begin();
         itr != database->relations.end(); itr++) {
             if (itr->first == name) {
                 dbRel = itr->second;
                 break;
             }
         }
    // Create a copy of the relation from the DataBase so we don't overwrite it
    std::vector<std::string> cpHeader(dbRel->getHeader()->getHeader());
    Header* finalRelHeader = new Header(cpHeader);
    Relation* finalRel = new Relation(dbRel->getName(), finalRelHeader);
    for (Tuple t : dbRel->getTuples()) {
        finalRel->AddTuple(t);
    }

    // Evaluate the Predicate
    for (unsigned int i = 0; i < p->parameters.size(); i++) {
        if (p->parameters.at(i)->isConstant) {  // This is a constant
            Relation* selectRel = finalRel->Select(i, p->parameters.at(i)->toString());
            delete finalRel;
            finalRel = selectRel;
        } else {    // This is a variable
            std::map<std::string, int>::iterator varItr = variables.find(p->parameters.at(i)->toString());
            if (varItr != variables.end()) {    // We've seen this variable before
                Relation* selectRel = finalRel->Select(varItr->second, i);
                delete finalRel;
                finalRel = selectRel;
            } else {    // We haven't seen this variable before
                variables.insert(std::pair<std::string, int> (p->parameters.at(i)->toString(), i));
                varNames.push_back(p->parameters.at(i)->toString());
            }
        }
    }
    // If any variables were present, do the following
    if (!varNames.empty()) {
        // Project the columns that had variables in the query; Exclude the constants
        std::vector<int> varPos;
        for (unsigned int j = 0; j < varNames.size(); j++) {
            std::map<std::string, int>::iterator itr = variables.find(varNames.at(j));
            varPos.push_back(itr->second);
        }
        Relation* projRel = finalRel->Project(varPos);
        delete finalRel;
        finalRel = projRel;
        // Create new Header with variable names
        // Pass new Header into Rename function
        Header* varHeader = new Header(varNames);
        Relation* renameRel = finalRel->Rename(varHeader);
        delete finalRel;
        finalRel = renameRel;
    }

    return finalRel;
}