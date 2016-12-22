

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object
{
public:
    Object();

    virtual std::string toJson() = 0;
};

#endif
