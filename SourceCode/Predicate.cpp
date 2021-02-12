#include "Predicate.h"

Predicate::~Predicate() {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        delete parameters.at(i);
    }
    parameters.clear();
}

void Predicate::SetID(std::string input) {
    id = input;
}

void Predicate::AddParameters(std::vector<Parameter*> newParameters) {
    parameters = newParameters;
}

std::string Predicate::toString() {
    std::string finalString = id + "(";

    // Iterate through parameters and call toString()
    // Prepend a comma on every parameter after the first one
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i > 0) {
            finalString += ",";
        }
        finalString += parameters.at(i)->toString();
    }

    finalString += ")";

    return finalString;
}

