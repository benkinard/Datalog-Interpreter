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

Header* Relation::getHeader() const {
    return header;
}

std::set<Tuple> Relation::getTuples() const {
    return tuples;
}

void Relation::AddTuple(Tuple newTuple) {
    tuples.insert(newTuple);
}

Relation* Relation::Select(int position, std::string value) {
    Relation* newRel = new Relation(this->name, this->header);
    for (Tuple t : tuples) {
        if (t.getTuple().at(position) == value) {
            newRel->AddTuple(t);
        }
    }
    return newRel;
}

Relation* Relation::Select(int position1, int position2) {
    Relation* newRel = new Relation(this->name, this->header);
    for (Tuple t : tuples) {
        if (t.getTuple().at(position1) == t.getTuple().at(position2)) {
            newRel->AddTuple(t);
        }
    }
    return newRel;
}

std::string Relation::toString() {
    std::string finalString = name + '\n';
    for (Tuple t : tuples) {
        for (unsigned int i = 0; i < header->getHeader().size(); i++) {
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