#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
                SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDFILE};

class Token {
public:
    Token(TokenType type = UNDEFINED, std::string input = "", int lineNumber = -1);
    TokenType getType() const;
    std::string getValue() const;
    std::string toString();
private:
    TokenType type;
    std::string value;
    int lineNum;
};

#endif
