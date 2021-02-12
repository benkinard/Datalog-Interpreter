#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    DatalogProgram()= default;
    ~DatalogProgram();
    void AddScheme(Predicate* newScheme);
    void AddFact(Predicate* newFact);
    void AddRule(Rule* newRule);
    void AddQuery(Predicate* newQuery);
    void AddDomain(std::string newDomain);
    std::string toString();

private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;
    std::set<std::string> domain;
};

#endif
