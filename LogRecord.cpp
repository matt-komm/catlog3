#include "LogRecord.hpp"
#include "Logger.hpp"

LogRecord::LogRecord(const Logger* logger,  const LogLevel& level):
    _logger(logger),
    _level(level)
{
}

void LogRecord::processAndPropagate()
{
    _logger->propagate(*this);
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

