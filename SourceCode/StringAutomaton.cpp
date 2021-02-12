#include "StringAutomaton.h"

unsigned int StringAutomaton::Start(const std::string &input) {
    inputRead = 0;
    newLines = 0;
    s0(input);
    return inputRead;
}

void StringAutomaton::s0(const std::string &input) {
    if (input.at(inputRead) == '\'') {
        inputRead++;
        s1(input);
    }
}

void StringAutomaton::s1(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '\'') {
            inputRead++;
            s2(input);
        } else {
            if (input.at(inputRead) == '\n') {
                newLines++;
            }
            inputRead++;
            s1(input);
        }
    } else {
        inputRead = 0;
    }
}

void StringAutomaton::s2(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '\'') {
            inputRead++;
            s1(input);
        }
    }
}

