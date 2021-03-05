#ifndef TUPLE_H
#define TUPLE_H
#include <string>
#include <vector>

class Tuple {
public:
    Tuple() = default;
    Tuple(std::vector<std::string> vals);
    std::vector<std::string> getTuple() const;
    bool operator< (const Tuple& other) const;
private:
    std::vector<std::string> values;
};

#endif