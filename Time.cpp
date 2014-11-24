#include "Time.hpp"

Time::Time()
{
}

Time Time::now()
{
    Time t;
    return std::move(t);
}

/*
Class::Class(const Class& c)
{
}

Class::Class(Class&& c)
{
}

Class& Class::operator=(const Class& c)
{
    return *this;
}

Class& Class::operator=(Class&& c)
{
    return *this;
}

Class::~Class()
{
}
*/

