#include "Logger.hpp"

Logger::Logger(std::string name, LogLevel level):
    _name(name),
    _level(level)
{
}

Logger::Logger(Logger&& logger):
    _name(std::move(logger._name)),
    _level(logger._level)
{
}


Logger& Logger::operator=(Logger&& logger)
{
    _name=std::move(logger._name);
    _level=logger._level;
    return *this;
}



