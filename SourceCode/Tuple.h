#ifndef TUPLE_H
#define TUPLE_H
#include <string>
#include <vector>

class Tuple {
public:
    Tuple();
    ~Tuple();
private:
    std::vector<std::string> values;
};

#endif