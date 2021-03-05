#include "Tuple.h"

Tuple::Tuple(std::vector<std::string> vals) : values(vals) {}

std::vector<std::string> Tuple::getTuple() const {
    return values;
}

bool Tuple::operator<(const Tuple& other) const {
    return values < other.getTuple();
}