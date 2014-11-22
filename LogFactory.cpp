#include "LogFactory.hpp"

LogFactory::LogFactory()
{
}

LogFactory& LogFactory::getInstance()
{
    static LogFactory logFactory;
    return logFactory;
}

Logger& LogFactory::get(std::string name, LogLevel level)
{
    LogFactory& logFactory = getInstance();
    std::unordered_map<std::string,Logger>::iterator foundLogger = logFactory._loggers.find(name);
    if (foundLogger!=logFactory._loggers.end())
    {
        return foundLogger->second;
    }
    return (logFactory._loggers.insert(std::make_pair(std::move(name), Logger(name,level))).first)->second;
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

