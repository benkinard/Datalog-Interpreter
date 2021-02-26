#ifndef DATABASE_H
#define DATABASE_H
#include "Relation.h"
#include <vector>

class Database {
public:
    Database();
    ~Database();
    void AddRelation(Relation);
private:
    std::vector<Relation> relations;
};

#endif