#ifndef RULE_H
#define RULE_H
#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
    friend class Interpreter;
public:
    Rule() = default;
    ~Rule();
    void SetHeadPredicate(Predicate* input);
    void AddBodyPredicates(std::vector<Predicate*> bodyPreds);
    std::string toString();

private:
   Predicate* headPredicate;
   std::vector<Predicate*> predicates;
};

#endif
