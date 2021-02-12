#include "DatalogProgram.h"

DatalogProgram::~DatalogProgram() {
    for (unsigned int i = 0; i < schemes.size(); i++) {
        delete schemes.at(i);
    }
    schemes.clear();

    for (unsigned int i = 0; i < facts.size(); i++) {
        delete facts.at(i);
    }
    facts.clear();

    for (unsigned int i = 0; i < rules.size(); i++) {
        delete rules.at(i);
    }
    rules.clear();

    for (unsigned int i = 0; i < queries.size(); i++) {
        delete queries.at(i);
    }
    queries.clear();
}

void DatalogProgram::AddScheme(Predicate* newScheme) {
    schemes.push_back(newScheme);
}

void DatalogProgram::AddFact(Predicate* newFact) {
    facts.push_back(newFact);
}

void DatalogProgram::AddRule(Rule* newRule) {
    rules.push_back(newRule);
}

void DatalogProgram::AddQuery(Predicate* newQuery) {
    queries.push_back(newQuery);
}

void DatalogProgram::AddDomain(std::string newDomain) {
    domain.insert(newDomain);
}

std::string DatalogProgram::toString() {
    std::string finalString;

    // Print the Schemes
    finalString = "Schemes(" + std::to_string(schemes.size()) + "):\n";
    // Iterate through schemes and call toString()
    for (unsigned int i = 0; i < schemes.size(); i++) {
        finalString += "  " + schemes.at(i)->toString() + "\n";
    }

    // Print the Facts
    finalString += "Facts(" + std::to_string(facts.size()) + "):\n";
    // Iterate through facts and call toString()
    for (unsigned int i = 0; i < facts.size(); i++) {
        finalString += "  " + facts.at(i)->toString() + ".\n";
    }

    // Print the Rules
    finalString += "Rules(" + std::to_string(rules.size()) + "):\n";
    // Iterate through rules and call toString()
    for (unsigned int i = 0; i < rules.size(); i++) {
        finalString += "  " + rules.at(i)->toString() + ".\n";
    }

    // Print the Queries
    finalString += "Queries(" + std::to_string(queries.size()) + "):\n";
    // Iterate through queries and call toString()
    for (unsigned int i = 0; i < queries.size(); i++) {
        finalString += "  " + queries.at(i)->toString() + "?\n";
    }

    // Print the Domain
    finalString += "Domain(" + std::to_string(domain.size()) + "):\n";
    // Print the Domain set
    for (std::set<std::string>::iterator iter = domain.begin(); iter != domain.end(); iter++) {
        finalString += "  " + *iter + "\n";
    }

    return finalString;
}

