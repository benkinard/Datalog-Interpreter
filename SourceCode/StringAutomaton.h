#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton {
public:
    StringAutomaton() : Automaton(STRING){}
    unsigned int Start(const std::string& input);

private:
    void s0(const std::string& input);
    void s1(const std::string& input);
    void s2(const std::string& input);
};

#endif
