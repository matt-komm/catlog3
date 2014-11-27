#include "LogChannel.hpp"

LogChannel::LogChannel(const std::string& name, const LogLevel& level) noexcept:
    _name(name),
    _level(level)
{
}

LogChannel::LogChannel(LogChannel&& logChannel):
    _name(std::move(logChannel._name)),
    _level(std::move(logChannel._level)),
    _handlers(std::move(logChannel._handlers))
{
    logChannel._handlers.clear();
}

LogChannel& LogChannel::operator=(LogChannel&& logChannel)
{
    _name = std::move(logChannel._name);
    _level = std::move(logChannel._level);
    for (unsigned int ihandler = 0; ihandler < _handlers.size(); ++ihandler)
    {
        delete _handlers[ihandler];
    }
    _handlers=std::move(logChannel._handlers);
    logChannel._handlers.clear();
    return *this;
}

void LogChannel::propagate(const LogRecord& logRecord) const
{
    if (logRecord.level()>=_level)
    {

    }
}


LogChannel::~LogChannel() noexcept
{
    for (unsigned int ihandler = 0; ihandler < _handlers.size(); ++ihandler)
    {
        delete _handlers[ihandler];
    }
}


