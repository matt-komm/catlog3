#include "LogFactory.hpp"

LogFactory::LogFactory()
{
}

LogFactory& LogFactory::getInstance()
{
    static LogFactory logFactory;
    return logFactory;
}

Logger& LogFactory::getLogger(std::string name, LogLevel level)
{
    LogFactory& logFactory = getInstance();
    std::unordered_map<std::string,Logger*>::iterator foundLogger = logFactory._loggers.find(name);
    if (foundLogger!=logFactory._loggers.end())
    {
        return *foundLogger->second;
    }
    return *(logFactory._loggers.insert(std::make_pair(std::move(name), new Logger(name,level))).first)->second;
}

LogChannel& LogFactory::getLogChannel(std::string name, LogLevel level)
{
    LogFactory& logFactory = getInstance();
    std::unordered_map<std::string,LogChannel*>::iterator foundChannel = logFactory._channels.find(name);
    if (foundChannel!=logFactory._channels.end())
    {
        return *foundChannel->second;
    }
    return *(logFactory._channels.insert(std::make_pair(std::move(name), new LogChannel(name,level))).first)->second;
}

LogFactory::~LogFactory()
{
    for (std::unordered_map<std::string,Logger*>::iterator it = _loggers.begin(); it != _loggers.end(); ++it)
    {
        delete it->second;
    }
    for (std::unordered_map<std::string,LogChannel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        delete it->second;
    }
    for (std::unordered_map<std::string,LogHandler*>::iterator it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        delete it->second;
    }
}

