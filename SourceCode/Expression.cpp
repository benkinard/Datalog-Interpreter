#include "Expression.h"

Expression::~Expression() {
    for (unsigned int i = 0; i < bothParameters.size(); i++) {
        delete bothParameters.at(i);
    }
    bothParameters.clear();
}

Expression::Expression(std::vector<Parameter *> params, std::string addmult) {
    bothParameters = params;
    oper = addmult;
}

std::string Expression::toString() {
    return ("(" + bothParameters[0]->toString() + oper + bothParameters[1]->toString() +")");
}

