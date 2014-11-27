#include "Logger.hpp"
#include "LogChannel.hpp"
#include "LogFactory.hpp"

Logger::Logger(const std::string& name, const LogLevel& level) noexcept:
    _name(name),
    _level(level)
{
    _channels.push_back(&LogFactory::getLogChannel(name,level));
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

void Logger::emit(const LogRecord& logRecord) const
{
    for (unsigned int ichannel = 0; ichannel < _channels.size(); ++ichannel)
    {
        _channels[ichannel]->propagate(logRecord);
    }
}

Logger::~Logger() noexcept
{

}
