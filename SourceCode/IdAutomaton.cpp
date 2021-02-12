#include "IdAutomaton.h"
#include <cctype>

unsigned int IdAutomaton::Start(const std::string &input) {
    inputRead = 0;
    s0(input);
    return inputRead;
}

void IdAutomaton::s0(const std::string &input) {
    if (isalpha(input.at(inputRead))) {
        inputRead++;
        s1(input);
    }
}

void IdAutomaton::s1(const std::string &input) {
    if (isalnum(input.at(inputRead))) {
        inputRead++;
        s1(input);
    }
}

