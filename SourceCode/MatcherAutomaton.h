#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H
#include "Automaton.h"

class MatcherAutomaton : public Automaton {
public:
    MatcherAutomaton(TokenType tokenType, std::string matchString) : Automaton(tokenType), toMatch(matchString){
    }
    unsigned int Start(const std::string& input);
private:
    std::string toMatch;
};

#endif
