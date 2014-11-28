#include "Logger.hpp"
#include "LogChannel.hpp"
#include "LogFactory.hpp"

Logger::Logger(const std::string& name, const LogLevel& level) noexcept:
    LogChannel(name,level)
{
}

Logger::Logger(Logger&& logger):
    LogChannel(std::move(logger))
{
}


Logger& Logger::operator=(Logger&&)
{
    return *this;
}

Logger::~Logger() noexcept
{

}
