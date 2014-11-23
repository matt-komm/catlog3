#include "Logger.hpp"

Logger::Logger(std::string name, LogLevel level) noexcept:
    _name(name),
    _level(level),
    _parent(nullptr)
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



