#ifndef DATABASE_H
#define DATABASE_H
#include "Relation.h"
#include <map>

class Database {
    friend class Interpreter;
public:
    Database() = default;
    ~Database();
    void AddRelation(Relation* newRelation);
    void PrintRelations();
private:
    std::map<std::string, Relation*> relations;
};

#endif