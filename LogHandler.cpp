#include "LogHandler.hpp"

LogHandler::LogHandler(const std::string& name, const LogLevel& level):
    LogChannel(name,level)
{
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

