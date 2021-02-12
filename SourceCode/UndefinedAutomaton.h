#ifndef UNDEFINEDAUTOMATON_H
#define UNDEFINEDAUTOMATON_H
#include "Automaton.h"

class UndefinedAutomaton : public Automaton {
public:
    UndefinedAutomaton() : Automaton(UNDEFINED){};
    unsigned int Start(const std::string& input);

private:
    void s0(const std::string& input);
    void s1a(const std::string& input);
    void s1b(const std::string& input);
    void s2a(const std::string& input);
    void s2b(const std::string& input);
    void s3(const std::string& input);
};

#endif
