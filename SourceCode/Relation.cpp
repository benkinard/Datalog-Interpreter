#include "Relation.h"

Relation::Relation(std::string name, Header* schema) {
    this->name = name;
    header = schema;
}

Relation::~Relation() {
    delete header;
    header = nullptr;
    tuples.clear();
}

std::string Relation::getName() const {
    return name;
}

void Relation::AddTuple(Tuple newTuple) {
    tuples.insert(newTuple);
}

std::string Relation::toString() {
    std::string finalString = name + '\n';
    for (Tuple t : tuples) {
        for (int i = 0; i < header->getHeader().size(); i++) {
            if (i != 0) {
                finalString += ", ";
            } else {
                finalString += "  ";
            }
            finalString += header->getHeader().at(i) + "='" + t.getTuple().at(i) + "'";
        }
        finalString += '\n';
    }
    return finalString;
}