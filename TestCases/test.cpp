#include "Database.h"
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    Database db;
    std::vector<std::string> abc;
    abc.push_back("A");
    abc.push_back("B");
    abc.push_back("C");
    std::vector<std::string> tup1;
    tup1.push_back("1");
    tup1.push_back("2");
    tup1.push_back("3");
    Tuple firstTuple(tup1);
    std::vector<std::string> tup2;
    tup2.push_back("4");
    tup2.push_back("5");
    tup2.push_back("6");
    Tuple secondTuple(tup2);
    auto columns = new Header(abc);
    auto table = new Relation("ABC", columns);
    table->AddTuple(secondTuple);
    table->AddTuple(firstTuple);

    db.AddRelation(table);
    db.PrintRelations();

    return 0;
}