#pragma once
#include <string>

class EWorld: public std::exception {
private:
    const char* msg;
public:
    EWorld(const std::string message);
    virtual const char* what() const throw();
};
