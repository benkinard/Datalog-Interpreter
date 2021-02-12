#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H
#include "Automaton.h"

class IdAutomaton : public Automaton {
public:
    IdAutomaton() : Automaton(ID){}
    unsigned int Start(const std::string& input);

private:
    void s0(const std::string& input);
    void s1(const std::string& input);
};

#endif
