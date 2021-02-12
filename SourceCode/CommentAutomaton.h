#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H
#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton() : Automaton(COMMENT){}
    unsigned int Start(const std::string& input);

private:
    void s0(const std::string& input);
    void s1(const std::string& input);
    void s2a(const std::string& input);
    void s2b(const std::string& input);
    void s3(const std::string& input);
};

#endif
