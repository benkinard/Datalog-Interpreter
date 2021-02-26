#ifndef RELATION_H
#define RELATION_H
#include "Header.h"
#include "Tuple.h"
#include <string>
#include <list>
#include <set>

class Relation {
public:
    Relation();
    ~Relation();
    Relation* Select(int position, std::string value);
    Relation* Select(int position1, int position2);
    Relation* Project(std::list<int> positions);
    Relation* Rename(std::list<std::string> names);
private:
    std::string name;
    Header* header;
    std::set<Tuple> tuples;
};

#endif