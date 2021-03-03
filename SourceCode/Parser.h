#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include <iostream>
#include <vector>

class Parser {
public:
    Parser() : datalogProgram(new DatalogProgram()){};
    ~Parser() = default;
    DatalogProgram* Parse(std::vector<Token*> input);

private:
    void ParseDatalogProgram(std::vector<Token*> input);
    void ParseScheme(std::vector<Token*> input);
    void ParseSchemeList(std::vector<Token*> input);
    void ParseFact(std::vector<Token*> input);
    void ParseFactList(std::vector<Token*> input);
    void ParseRule(std::vector<Token*> input);
    void ParseRuleList(std::vector<Token*> input);
    void ParseQuery(std::vector<Token*> input);
    void ParseQueryList(std::vector<Token*> input);
    void ParseIdList(std::vector<Token*> input);
    void ParseStringList(std::vector<Token*> input);
    void ParseHeadPredicate(std::vector<Token*> input);
    void ParsePredicate(std::vector<Token*> input);
    void ParsePredicateList(std::vector<Token*> input);
    void ParseParameter(std::vector<Token*> input);
    void ParseParameterList(std::vector<Token*> input);
    void ParseExpression(std::vector<Token*> input);
    void ParseOperator(std::vector<Token*> input);
    void Match(std::vector<Token*> input, TokenType reqToken);
    unsigned int currentIndex = 0;

    DatalogProgram* datalogProgram;
    std::vector<Parameter*> tempParameters;
    Predicate* tempHeadPredicate;
    std::vector<Predicate*> tempPredicates;
    std::vector<Parameter*> tempExpression;
    std::string tempOperator;
};


#endif
