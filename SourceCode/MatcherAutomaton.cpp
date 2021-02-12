#include "MatcherAutomaton.h"

unsigned int MatcherAutomaton::Start(const std::string &input) {
    bool isMatch = true;
    inputRead = 0;
    for (unsigned int i = 0; i < toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
    return inputRead;
}

