#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <vector>

class Header {
public:
    Header(std::vector<std::string> schema);
    std::vector<std::string> getHeader() const;
private:
    std::vector<std::string> attributes;
};

#endif