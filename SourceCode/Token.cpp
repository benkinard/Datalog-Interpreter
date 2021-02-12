#include "Token.h"

Token::Token(TokenType type, std::string input, int lineNumber) {
    this->type = type;
    value = input;
    lineNum = lineNumber;
}

TokenType Token::getType() const {
    return type;
}

std::string Token::getValue() const {
    return value;
}

std::string Token::toString() {
    std::string typeAsString;
    switch (type) {
        case COMMA: typeAsString = "COMMA"; break;
        case PERIOD: typeAsString = "PERIOD"; break;
        case Q_MARK: typeAsString = "Q_MARK"; break;
        case LEFT_PAREN: typeAsString = "LEFT_PAREN"; break;
        case RIGHT_PAREN: typeAsString = "RIGHT_PAREN"; break;
        case COLON: typeAsString = "COLON"; break;
        case COLON_DASH: typeAsString = "COLON_DASH"; break;
        case MULTIPLY: typeAsString = "MULTIPLY"; break;
        case ADD: typeAsString = "ADD"; break;
        case SCHEMES: typeAsString = "SCHEMES"; break;
        case FACTS: typeAsString = "FACTS"; break;
        case RULES: typeAsString = "RULES"; break;
        case QUERIES: typeAsString = "QUERIES"; break;
        case ID: typeAsString = "ID"; break;
        case STRING: typeAsString = "STRING"; break;
        case COMMENT: typeAsString = "COMMENT"; break;
        case UNDEFINED: typeAsString = "UNDEFINED"; break;
        case ENDFILE: typeAsString = "EOF"; break;
    }

    return "(" + typeAsString + ",\"" + value + "\"," + std::to_string(lineNum) + ")";
}

