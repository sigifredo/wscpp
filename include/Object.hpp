

#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object
{
public:
    Object();

    virtual std::string toJson() = 0;
};

#endif
