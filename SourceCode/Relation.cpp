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
    // Create new Relation with same name and same header
    Relation* newRel = new Relation(this->name, this->header);
    // In this new Relation, only include Tuples with values that match
    // the given value for the given position/column
    for (Tuple t : tuples) {
        if (t.getTuple().at(position) == value) {
            newRel->AddTuple(t);
        }
    }
    return newRel;
}

Relation* Relation::Select(int position1, int position2) {
    // Create new Relation with same name and same header
    Relation* newRel = new Relation(this->name, this->header);
    // In this new Relation, only include the Tuples with matching values
    // at the given positions
    for (Tuple t : tuples) {
        if (t.getTuple().at(position1) == t.getTuple().at(position2)) {
            newRel->AddTuple(t);
        }
    }
    return newRel;
}

Relation* Relation::Project(std::vector<int> positions) {
    // Create header for projected columns
    std::vector<std::string> projCols;
    for (int i = 0; i < positions.size(); i++) {
        projCols.push_back(this->header->getHeader().at(positions.at(i)));
    }
    Header* newHeader = new Header(projCols);
    // Create new Relation with same name and new header
    Relation* newRel = new Relation(this->name, newHeader);
    // Create new Tuples that only include the projected columns
    // Add these new Tuples to the new Relation
    for (Tuple t : tuples) {
        std::vector<std::string> values;
        for (int k = 0; k < positions.size(); k++) {
            values.push_back(t.getTuple().at(positions.at(k)));
        }
        Tuple nt(values);
        newRel->AddTuple(nt);
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