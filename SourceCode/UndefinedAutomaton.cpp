#include "UndefinedAutomaton.h"

unsigned int UndefinedAutomaton::Start(const std::string &input) {
    inputRead = 0;
    newLines = 0;
    s0(input);
    return inputRead;
}

void UndefinedAutomaton::s0(const std::string &input) {
    if (input.at(inputRead) == '#') {
        inputRead++;
        s1b(input);
    } else if (input.at(inputRead) == '\'') {
        inputRead++;
        s1a(input);
    }
}

void UndefinedAutomaton::s1a(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '\'') {
            inputRead++;
            s2a(input);
        } else {
            if (input.at(inputRead) == '\n') {
                newLines++;
            }
            inputRead++;
            s1a(input);
        }
    }
}

void UndefinedAutomaton::s1b(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '|') {
            inputRead++;
            s2b(input);
        } else {
            inputRead = 0;
        }
    } else {
        inputRead = 0;
    }
}

void UndefinedAutomaton::s2a(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '\'') {
            inputRead++;
            s1a(input);
        } else {
            inputRead = 0;
        }
    } else {
        inputRead = 0;
    }
}

void UndefinedAutomaton::s2b(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '|') {
            inputRead++;
            s3(input);
        } else {
            if (input.at(inputRead) == '\n') {
                newLines++;
            }
            inputRead++;
            s2b(input);
        }
    }
}

void UndefinedAutomaton::s3(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '#') {
            inputRead = 0;
        } else {
            if (input.at(inputRead) == '\n') {
                newLines++;
            }
            inputRead++;
            s2b(input);
        }
    }
}

