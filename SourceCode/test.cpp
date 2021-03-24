#include "Relation.h"
#include "Tuple.h"
#include "Header.h"
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::string> header;
    header.push_back("X");
    header.push_back("Y");
    header.push_back("Z");
    // Create "database" relation
    Header* hDB = new Header(header);
    Relation* rDB = new Relation("Test", hDB);

    // Create tuples and add to "database" relation
    std::vector<std::string> tuplesDB;
    tuplesDB.push_back("A");
    tuplesDB.push_back("B");
    tuplesDB.push_back("C");
    Tuple tuple1(tuplesDB);
    rDB->AddTuple(tuple1);
    tuplesDB.clear();

    tuplesDB.push_back("1");
    tuplesDB.push_back("2");
    tuplesDB.push_back("3");
    Tuple tuple2(tuplesDB);
    rDB->AddTuple(tuple2);
    tuplesDB.clear();

    std::cout << "Initial database relation" << std::endl;
    std::cout << rDB->toString() << std::endl;

    // Create "rule evaluation" relation
    header.clear();
    header.push_back("D");
    header.push_back("E");
    header.push_back("F");
    Header* hRE = new Header(header);
    Relation* rRE = new Relation("Test", hRE);

    // Create tuples and add to "rule evaluation" relation
    std::vector<std::string> tuplesRE;
    tuplesRE.push_back("A");
    tuplesRE.push_back("B");
    tuplesRE.push_back("C");
    Tuple tuple3(tuplesRE);
    rRE->AddTuple(tuple3);
    tuplesRE.clear();

    tuplesRE.push_back("4");
    tuplesRE.push_back("5");
    tuplesRE.push_back("6");
    Tuple tuple4(tuplesRE);
    rRE->AddTuple(tuple4);
    tuplesRE.clear();

    std::cout << "Rule evaluation relation" << std::endl;
    std::cout << rRE->toString() << std::endl;

    // Test Union Operator Method
    std::cout << "Performing Union" << std::endl;
    rDB->UnionOp(rRE);

    std::cout << "Database Relation following Union" << std::endl;
    std::cout << rDB->toString() << std::endl;

    return 0;
}