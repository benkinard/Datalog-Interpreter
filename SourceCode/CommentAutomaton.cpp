#include "CommentAutomaton.h"

unsigned int CommentAutomaton::Start(const std::string &input) {
    inputRead = 0;
    newLines = 0;
    s0(input);
    return inputRead;
}

void CommentAutomaton::s0(const std::string &input) {
    if (input.at(inputRead) == '#') {
        inputRead++;
        s1(input);
    }
}

void CommentAutomaton::s1(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '|') {
            inputRead++;
            s2b(input);
        } else if (input.at(inputRead) != '\n') {
            inputRead++;
            s2a(input);
        }
    }
}

void CommentAutomaton::s2a(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) != '\n') {
            inputRead++;
            s2a(input);
        }
    }
}

void CommentAutomaton::s2b(const std::string &input) {
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
    } else {
        inputRead = 0;
    }
}

void CommentAutomaton::s3(const std::string &input) {
    if (inputRead < input.size()) {
        if (input.at(inputRead) == '|') {
            inputRead++;
            s3(input);
        } else if (input.at(inputRead) == '#') {
            inputRead++;
        } else {
            if (input.at(inputRead) == '\n') {
                newLines++;
            }
            inputRead++;
            s2b(input);
        }
    } else {
        inputRead = 0;
    }
}

