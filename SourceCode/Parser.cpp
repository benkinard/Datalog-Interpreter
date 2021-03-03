#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
#include "PlainParameter.h"
#include "Expression.h"

DatalogProgram* Parser::Parse(std::vector<Token *> input) {
    try {
        try {
            // Run input through Parser
            ParseDatalogProgram(input);
            std::cout << "Success!" << std::endl;
            // Print datalog program
            std::cout << datalogProgram->toString();
        } catch (unsigned int index) {
            // Catch program that does not end with an EOF
            std::cout << "Failure!" << std::endl;
            std::cout << "  No EOF Token found" << std::endl;
            std::cout << "  Current Index \"" << index << "\" is out of range" << std::endl;
        }
    } catch (Token* error) {
        // Catch program that does not comply with Datalog Grammar
        std::cout << "Failure!" << std::endl << "  ";
        std::cout << error->toString() << std::endl;
    }
    return datalogProgram;
}

void Parser::ParseDatalogProgram(std::vector<Token *> input) {
    Match(input, SCHEMES);
    Match(input, COLON);
    ParseScheme(input);
    ParseSchemeList(input);
    Match(input, FACTS);
    Match(input, COLON);
    ParseFactList(input);
    Match(input, RULES);
    Match(input, COLON);
    ParseRuleList(input);
    Match(input, QUERIES);
    Match(input, COLON);
    ParseQuery(input);
    ParseQueryList(input);
    Match(input, ENDFILE);
}

void Parser::ParseScheme(std::vector<Token *> input) {
    // Create scheme object
    auto schemeObject = new Predicate();
    Match(input, ID);
    schemeObject->SetID(input.at(currentIndex - 1)->getValue());
    Match(input, LEFT_PAREN);
    Match(input, ID);
    auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
    // append parameter to temporary vector storing parameters for this scheme object
    tempParameters.push_back(newPlainParameter);
    ParseIdList(input);
    // Add the parameters that were appended to tempParameters to the scheme object
    //  then clear tempParameters so it is ready to be used for subsequent objects
    schemeObject->AddParameters(tempParameters);
    tempParameters.clear();
    Match(input, RIGHT_PAREN);
    // Add scheme object to datalog program
    datalogProgram->AddScheme(schemeObject);
}

void Parser::ParseSchemeList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == ID) {
            ParseScheme(input);
            ParseSchemeList(input);
        } else if (input.at(currentIndex)->getType() == FACTS) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseFact(std::vector<Token *> input) {
    // Create fact object
    auto factObject = new Predicate();
    Match(input, ID);
    factObject->SetID(input.at(currentIndex - 1)->getValue());
    Match(input, LEFT_PAREN);
    Match(input, STRING);
    auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
    // Add parameter to the set of domains and append it to tempParameters
    datalogProgram->AddDomain(newPlainParameter->toString());
    tempParameters.push_back(newPlainParameter);
    ParseStringList(input);
    // Add the parameters that were appended to tempParameters to the fact object
    //  then clear tempParameters so it is ready to be used by subsequent objects
    factObject->AddParameters(tempParameters);
    tempParameters.clear();
    Match(input, RIGHT_PAREN);
    Match(input, PERIOD);
    // Add fact object to datalog program
    datalogProgram->AddFact(factObject);
}

void Parser::ParseFactList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == ID) {
            ParseFact(input);
            ParseFactList(input);
        } else if (input.at(currentIndex)->getType() == RULES) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseRule(std::vector<Token *> input) {
    // Create rule object
    auto ruleObject = new Rule();
    ParseHeadPredicate(input);
    // Add predicate stored in tempHeadPredicate to rule object
    //  then clear tempHeadPredicate so it is ready to be used for subsequent rule objects
    ruleObject->SetHeadPredicate(tempHeadPredicate);
    tempHeadPredicate = nullptr;
    Match(input, COLON_DASH);
    ParsePredicate(input);
    ParsePredicateList(input);
    // Add predicates stored in tempPredicates to rule object
    //  then clear tempPredicates so it is ready to be used for subsequent rule objects
    ruleObject->AddBodyPredicates(tempPredicates);
    tempPredicates.clear();
    Match(input, PERIOD);
    // Add rule object to datalog program
    datalogProgram->AddRule(ruleObject);
}

void Parser::ParseRuleList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == ID) {
            ParseRule(input);
            ParseRuleList(input);
        } else if (input.at(currentIndex)->getType() == QUERIES) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseQuery(std::vector<Token *> input) {
    ParsePredicate(input);
    // Create query object and add predicates from tempPredicates to it
    //  then clear tempPredicates so it is ready to be used for future objects
    Predicate* queryObject = tempPredicates.at(0);
    tempPredicates.clear();
    Match(input, Q_MARK);
    // Add query object to datalog program
    datalogProgram->AddQuery(queryObject);
}

void Parser::ParseQueryList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == ID) {
            ParseQuery(input);
            ParseQueryList(input);
        } else if (input.at(currentIndex)->getType() == ENDFILE) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseIdList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == COMMA) {
            Match(input, COMMA);
            Match(input, ID);
            auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
            tempParameters.push_back(newPlainParameter);
            ParseIdList(input);
        } else if (input.at(currentIndex)->getType() == RIGHT_PAREN) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseStringList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == COMMA) {
            Match(input, COMMA);
            Match(input, STRING);
            auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
            datalogProgram->AddDomain(newPlainParameter->toString());
            tempParameters.push_back(newPlainParameter);
            ParseStringList(input);
        } else if (input.at(currentIndex)->getType() == RIGHT_PAREN) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseHeadPredicate(std::vector<Token *> input) {
    auto headPredicateObject = new Predicate();
    Match(input, ID);
    headPredicateObject->SetID(input.at(currentIndex - 1)->getValue());
    Match(input, LEFT_PAREN);
    Match(input, ID);
    auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
    tempParameters.push_back(newPlainParameter);
    ParseIdList(input);
    headPredicateObject->AddParameters(tempParameters);
    tempParameters.clear();
    Match(input, RIGHT_PAREN);
    tempHeadPredicate = headPredicateObject;
}

void Parser::ParsePredicate(std::vector<Token *> input) {
    auto newPredicateObject = new Predicate();
    Match(input, ID);
    newPredicateObject->SetID(input.at(currentIndex - 1)->getValue());
    Match(input, LEFT_PAREN);
    ParseParameter(input);
    ParseParameterList(input);
    newPredicateObject->AddParameters(tempParameters);
    tempParameters.clear();
    Match(input, RIGHT_PAREN);
    tempPredicates.push_back(newPredicateObject);
}

void Parser::ParsePredicateList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == COMMA) {
            Match(input, COMMA);
            ParsePredicate(input);
            ParsePredicateList(input);
        } else if (input.at(currentIndex)->getType() == PERIOD) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseParameter(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == STRING) {
            Match(input, STRING);
            auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
            tempParameters.push_back(newPlainParameter);
        } else if (input.at(currentIndex)->getType() == ID) {
            Match(input, ID);
            auto newPlainParameter = new PlainParameter(input.at(currentIndex - 1)->getValue());
            tempParameters.push_back(newPlainParameter);
        } else if (input.at(currentIndex)->getType() == LEFT_PAREN) {
            ParseExpression(input);
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseParameterList(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == COMMA) {
            Match(input, COMMA);
            ParseParameter(input);
            ParseParameterList(input);
        } else if (input.at(currentIndex)->getType() == RIGHT_PAREN) {
            return;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::ParseExpression(std::vector<Token *> input) {
    Match(input, LEFT_PAREN);
    ParseParameter(input);
    ParseOperator(input);
    std::string exprOperator = tempOperator;
    ParseParameter(input);
    Match(input, RIGHT_PAREN);
    // Creat an expression object with the previous two parameters appended to tempParameters
    //  and the operator that operates on them.
    //  Replace those two parameters that are on tempParameters with the Expression object that now holds them
    tempExpression.push_back(tempParameters.at(tempParameters.size() - 2));
    tempExpression.push_back(tempParameters.at(tempParameters.size() - 1));
    tempParameters.pop_back();
    tempParameters.pop_back();
    auto expressionObject = new Expression(tempExpression, exprOperator);
    tempExpression.clear();
    tempParameters.push_back(expressionObject);
}

void Parser::ParseOperator(std::vector<Token *> input) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == ADD) {
            Match(input, ADD);
            tempOperator = input.at(currentIndex - 1)->getValue();
        } else if (input.at(currentIndex)->getType() == MULTIPLY) {
            Match(input, MULTIPLY);
            tempOperator = input.at(currentIndex - 1)->getValue();
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}

void Parser::Match(std::vector<Token *> input, TokenType reqToken) {
    if (currentIndex < input.size()) {
        if (input.at(currentIndex)->getType() == reqToken) {
            currentIndex++;
        } else {
            throw input.at(currentIndex);
        }
    } else {
        throw currentIndex;
    }
}