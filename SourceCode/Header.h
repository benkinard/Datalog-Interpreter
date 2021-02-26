#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <vector>

class Header {
public:
    Header();
    ~Header();
private:
    std::vector<std::string> attributes;
};

#endif