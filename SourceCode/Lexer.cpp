#include <iostream>
#include "Lexer.h"

Lexer::Lexer() {
    automata.push_back(new MatcherAutomaton(COMMA, ","));
    automata.push_back(new MatcherAutomaton(PERIOD, "."));
    automata.push_back(new MatcherAutomaton(Q_MARK, "?"));
    automata.push_back(new MatcherAutomaton(LEFT_PAREN, "("));
    automata.push_back(new MatcherAutomaton(RIGHT_PAREN, ")"));
    automata.push_back(new MatcherAutomaton(COLON, ":"));
    automata.push_back(new MatcherAutomaton(COLON_DASH, ":-"));
    automata.push_back(new MatcherAutomaton(MULTIPLY, "*"));
    automata.push_back(new MatcherAutomaton(ADD, "+"));
    automata.push_back(new MatcherAutomaton(SCHEMES, "Schemes"));
    automata.push_back(new MatcherAutomaton(FACTS, "Facts"));
    automata.push_back(new MatcherAutomaton(RULES, "Rules"));
    automata.push_back(new MatcherAutomaton(QUERIES, "Queries"));
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new UndefinedAutomaton());
}

Lexer::~Lexer() {
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        delete tokens.at(i);
    }
    tokens.clear();

    for (unsigned int j = 0; j < automata.size(); ++j) {
        delete automata.at(j);
    }
    automata.clear();
}

void Lexer::Run(std::string input) {
    int currentLine = 1;
    while (input.size() > 0) {      // While there are more characters to be read
        unsigned int maxRead = 0;
        Automaton* maxAutomaton = automata[0];
        while (isspace(input.at(0))) {      // Remove WS that is not part of strings or comments
            if (input[0] == '\n') {
                currentLine++;
            }
            if (input.size() > 1) {
                input = input.substr(1, input.size() - 1);
            } else {
                input = "";
                break;
            }
        }
        if (input.size() > 0) {
            for (unsigned int i = 0; i < automata.size(); i++) {     // Run the input through each automaton
                unsigned int inputRead = automata[i]->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata[i];
                }
            }
            if (maxRead > 0) {      // If any of the automata reached an accept state
                Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), currentLine);
                currentLine += maxAutomaton->NewLinesRead();
                if (newToken->getType() != COMMENT) {
                    tokens.push_back(newToken);
                } else {
                    delete newToken;
                }
            } else {        // If none of the automata reached an accept state
                maxRead = 1;
                auto unDef = new UndefinedAutomaton();
                Token* newToken = unDef->CreateToken(input.substr(0, maxRead), currentLine);
                currentLine += unDef->NewLinesRead();
                tokens.push_back(newToken);
            }
            if (input.size() > maxRead) {       // Remove the read-in characters from the input string
                input = input.substr(maxRead, input.size() - maxRead);
            } else {
                input = "";
            }
        }
    }
    auto newToken = new Token(ENDFILE, "", currentLine);  // Add EOF token
    tokens.push_back(newToken);
}

std::vector<Token*> Lexer::getTokens() const {
    return tokens;
}

void Lexer::PrintTokens() const {
    for (unsigned int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i]->toString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size() << std::endl;
}

