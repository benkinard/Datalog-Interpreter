#include "Relation.h"
#include "Tuple.h"
#include "Header.h"
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::string> header;
    header.push_back("cat");
    header.push_back("dog");
    header.push_back("fish");
    // Create "database" relation
    Header* hDB = new Header(header);
    Relation* rDB = new Relation("alpha", hDB);

    // Create tuples and add to "database" relation
    std::vector<std::string> tuplesDB;
    tuplesDB.push_back("1");
    tuplesDB.push_back("2");
    tuplesDB.push_back("5");
    Tuple tuple1(tuplesDB);
    rDB->AddTuple(tuple1);
    tuplesDB.clear();

    tuplesDB.push_back("1");
    tuplesDB.push_back("4");
    tuplesDB.push_back("1");
    Tuple tuple2(tuplesDB);
    rDB->AddTuple(tuple2);
    tuplesDB.clear();

    tuplesDB.push_back("2");
    tuplesDB.push_back("3");
    tuplesDB.push_back("2");
    Tuple tuple3(tuplesDB);
    rDB->AddTuple(tuple3);
    tuplesDB.clear();

    tuplesDB.push_back("3");
    tuplesDB.push_back("3");
    tuplesDB.push_back("2");
    Tuple tuple4(tuplesDB);
    rDB->AddTuple(tuple4);
    tuplesDB.clear();

    tuplesDB.push_back("6");
    tuplesDB.push_back("7");
    tuplesDB.push_back("4");
    Tuple tuple5(tuplesDB);
    rDB->AddTuple(tuple5);
    tuplesDB.clear();

    std::cout << "Relation alpha" << std::endl;
    std::cout << rDB->toString() << std::endl;

    // Create "rule evaluation" relation
    header.clear();
    header.push_back("cat");
    header.push_back("fish");
    header.push_back("bird");
    header.push_back("bunny");
    Header* hRE = new Header(header);
    Relation* rRE = new Relation("beta", hRE);

    // Create tuples and add to "rule evaluation" relation
    std::vector<std::string> tuplesRE;
    tuplesRE.push_back("3");
    tuplesRE.push_back("4");
    tuplesRE.push_back("2");
    tuplesRE.push_back("4");
    Tuple tuple6(tuplesRE);
    rRE->AddTuple(tuple6);
    tuplesRE.clear();

    tuplesRE.push_back("6");
    tuplesRE.push_back("4");
    tuplesRE.push_back("9");
    tuplesRE.push_back("2");
    Tuple tuple7(tuplesRE);
    rRE->AddTuple(tuple7);
    tuplesRE.clear();

    tuplesRE.push_back("4");
    tuplesRE.push_back("3");
    tuplesRE.push_back("2");
    tuplesRE.push_back("7");
    Tuple tuple8(tuplesRE);
    rRE->AddTuple(tuple8);
    tuplesRE.clear();

    tuplesRE.push_back("1");
    tuplesRE.push_back("5");
    tuplesRE.push_back("2");
    tuplesRE.push_back("4");
    Tuple tuple9(tuplesRE);
    rRE->AddTuple(tuple9);
    tuplesRE.clear();

    tuplesRE.push_back("1");
    tuplesRE.push_back("5");
    tuplesRE.push_back("8");
    tuplesRE.push_back("3");
    Tuple tuple10(tuplesRE);
    rRE->AddTuple(tuple10);
    tuplesRE.clear();

    std::cout << "Relation beta" << std::endl;
    std::cout << rRE->toString() << std::endl;

    // Test Join Method
    std::cout << "Performing Join" << std::endl;
    Relation* joinedRel = rDB->Join(rRE);

    std::cout << "Alpha following Join" << std::endl;
    std::cout << rDB->toString() << std::endl;

    std::cout << "Beta following Join" << std::endl;
    std::cout << rRE->toString() << std::endl;

    std::cout << "Joined Relation following Join" << std::endl;
    std::cout << joinedRel->toString() << std::endl;

    return 0;
}