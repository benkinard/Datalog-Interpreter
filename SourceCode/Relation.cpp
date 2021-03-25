#include "Relation.h"
#include <iostream>

Relation::Relation(std::string title, Header* schema) : name(title), header(schema) {}

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
    std::vector<std::string> cpHeader(this->header->getHeader());
    Header* newHeader = new Header(cpHeader);
    Relation* newRel = new Relation(this->name, newHeader);
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
    std::vector<std::string> cpHeader(this->header->getHeader());
    Header* newHeader = new Header(cpHeader);
    Relation* newRel = new Relation(this->name, newHeader);
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
    for (unsigned int i = 0; i < positions.size(); i++) {
        projCols.push_back(this->header->getHeader().at(positions.at(i)));
    }
    Header* newHeader = new Header(projCols);
    // Create new Relation with same name and new header
    Relation* newRel = new Relation(this->name, newHeader);
    // Create new Tuples that only include the projected columns
    // Add these new Tuples to the new Relation
    for (Tuple t : tuples) {
        std::vector<std::string> values;
        for (unsigned int k = 0; k < positions.size(); k++) {
            values.push_back(t.getTuple().at(positions.at(k)));
        }
        Tuple nt(values);
        newRel->AddTuple(nt);
    }
    return newRel;
}

Relation* Relation::Rename(Header* newHeader) {
    Relation* newRel = new Relation(this->name, newHeader);
    for (Tuple t : tuples) {
        newRel->AddTuple(t);
    }
    return newRel;
}

Relation* Relation::Join(Relation* otherRelation) {
    std::vector<std::string> h1 = this->getHeader()->getHeader();
    std::vector<std::string> h2 = otherRelation->getHeader()->getHeader();
    /*
    Store any matching column names in a map object.
    To make life easier later, store the index from the second header
    as the key and the index from the first header as the value
    */
    std::map<int, int> matchCols;
    for (unsigned int i = 0; i < h1.size(); i++) {
        for (unsigned int j = 0; j < h2.size(); j++) {
            if (h1.at(i) == h2.at(j)) {
                matchCols.insert(std::pair<int, int> (j, i));
            }
        }
    }
    // Combine the two headers into one
    Header* newHeader = combineHeaders(h1, h2, matchCols);
    // Create new empty relation with the combined header
    auto result = new Relation("result", newHeader);
    // Check every pair of Tuples to see if they can be joined
    for (const Tuple& t1 : tuples) {
        for (const Tuple& t2 : otherRelation->getTuples()) {
            if (isJoinable(t1, t2, matchCols)) {
                result->AddTuple(combineTuples(t1, t2, matchCols));
            }
        }
    }
    
    return result;
}

bool Relation::UnionOp(Relation* ruleEval) {
    bool anyNewTuples = false;
    for (Tuple t : ruleEval->getTuples()) {
        if (tuples.insert(t).second) {  // If tuple is new addition to relation, print it out
            anyNewTuples = true;
            std::string finalString;
            for (unsigned int i = 0; i < header->getHeader().size(); i++) {
                if (i != 0) {
                    finalString += ", ";
                } else {
                    finalString += "  ";
                }
                finalString += header->getHeader().at(i) + "=" + t.getTuple().at(i);
            }
            std::cout << finalString << std::endl;
        }
    }
    return anyNewTuples;
}

std::string Relation::toString() {
    std::string finalString;
    for (Tuple t : tuples) {
        for (unsigned int i = 0; i < header->getHeader().size(); i++) {
            if (i != 0) {
                finalString += ", ";
            } else {
                finalString += "  ";
            }
            finalString += header->getHeader().at(i) + "=" + t.getTuple().at(i);
        }
        finalString += '\n';
    }
    return finalString;
}

Header* Relation::combineHeaders(std::vector<std::string> h1, std::vector<std::string> h2, std::map<int, int> matchCols) {
    // Copy over all the column names from the first header into a new vector
    std::vector<std::string> combinedAttributes = h1;
    // Append any unique column names from the second header to this new vector
    for (unsigned int i = 0; i < h2.size(); i++) {
        std::map<int, int>::iterator itr = matchCols.find(i);
        if (itr == matchCols.end()) {
            combinedAttributes.push_back(h2.at(i));
        }
    }
    // Use this new vector to create a new Header* object
    auto newHeader = new Header(combinedAttributes);
    return newHeader;
}

bool Relation::isJoinable(const Tuple& t1, const Tuple& t2, std::map<int, int> matchCols) {
    if (!matchCols.empty()) {
        for (std::map<int, int>::iterator itr = matchCols.begin(); itr != matchCols.end(); itr++) {
            if (t1.getTuple().at(itr->second) != t2.getTuple().at(itr->first)) {
                return false;
            }
        }
    }
    return true;
}

Tuple Relation::combineTuples(const Tuple& t1, const Tuple& t2, std::map<int, int> matchCols) {
    // Copy over all the tuple values from the first tuple
    std::vector<std::string> combinedVals = t1.getTuple();
    // Append any tuple values from unique columns from the second tuple
    for (unsigned int i = 0; i < t2.getTuple().size(); i++) {
        std::map<int, int>::iterator itr = matchCols.find(i);
        if (itr == matchCols.end()) {
            combinedVals.push_back(t2.getTuple().at(i));
        }
    }
    // Use this new vector to create a new Tuple object
    Tuple newTuple(combinedVals);
    return newTuple;
}