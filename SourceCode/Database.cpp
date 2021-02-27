#include "Database.h"
#include <iostream>

Database::~Database() {
    for (std::map<std::string, Relation*>::iterator itr = relations.begin();
        itr != relations.end(); itr++) {
             delete itr->second;
    }
    relations.clear();
}

void Database::PrintRelations() {
    for (std::map<std::string, Relation*>::iterator itr = relations.begin();
        itr != relations.end(); itr++) {
            std::cout << itr->second->toString();
        }
}

void Database::AddRelation(Relation* newRelation) {
    relations.insert(std::pair<std::string, Relation*> (newRelation->getName(),
                                                       newRelation));
}