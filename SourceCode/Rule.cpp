#include "Rule.h"

Rule::~Rule() {
    delete headPredicate;
    headPredicate = nullptr;

    for (unsigned int i = 0; i < predicates.size(); i++) {
        delete predicates.at(i);
    }
    predicates.clear();
}

void Rule::SetHeadPredicate(Predicate *input) {
    headPredicate = input;
}

void Rule::AddBodyPredicates(std::vector<Predicate *> bodyPreds) {
    predicates = bodyPreds;
}

std::string Rule::toString() {
    std::string finalString;

    finalString = headPredicate->toString() + " :- ";

    for (unsigned int i = 0; i < predicates.size(); i++) {
        if (i > 0) {
            finalString += ",";
        }
        finalString += predicates.at(i)->toString();
    }

    return finalString;
}

