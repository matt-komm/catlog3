#include "LogChannel.hpp"

LogChannel::LogChannel(const std::string& name, const LogLevel& level) noexcept:
    _name(name),
    _level(level)
{
}

LogChannel::LogChannel(LogChannel&& logChannel):
    _name(std::move(logChannel._name)),
    _level(std::move(logChannel._level)),
    _channels(std::move(logChannel._channels))
{
    logChannel._channels.clear();
}

LogChannel& LogChannel::operator=(LogChannel&& logChannel)
{
    _name = std::move(logChannel._name);
    _level = std::move(logChannel._level);
    for (unsigned int ichannel = 0; ichannel < _channels.size(); ++ichannel)
    {
        delete _channels[ichannel];
    }
    _channels=std::move(logChannel._channels);
    logChannel._channels.clear();
    return *this;
}

void LogChannel::propagate(const LogRecord& logRecord) const
{
    if (this->effectiveLevel()<=logRecord.level())
    {
        for (unsigned int ichannel = 0; ichannel < _channels.size(); ++ichannel)
        {
            _channels[ichannel]->propagate(logRecord);
        }
    }
}


LogChannel::~LogChannel() noexcept
{
}


