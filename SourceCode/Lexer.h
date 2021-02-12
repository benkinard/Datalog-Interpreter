#ifndef LEXER_H
#define LEXER_H
#include "MatcherAutomaton.h"
#include "UndefinedAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include <vector>
#include <cctype>

class Lexer {
public:
    Lexer();
    ~Lexer();
    void Run(std::string input);
    std::vector<Token*> getTokens() const;
    void PrintTokens() const;
private:
    std::vector<Token*> tokens;
    std::vector<Automaton*> automata;
};

#endif
