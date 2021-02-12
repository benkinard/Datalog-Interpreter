#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"

class Automaton {
public:
    Automaton(TokenType type) {this->type = type;}
    virtual ~Automaton() {}
    virtual unsigned int Start(const std::string& input) = 0;
    virtual Token* CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber); }
    virtual int NewLinesRead() const { return newLines;}
protected:
    unsigned int inputRead = 0;
    int newLines = 0;
    TokenType type;
};

#endif
