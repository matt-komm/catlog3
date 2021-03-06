#ifndef __LOGFACTORY_H__
#define __LOGFACTORY_H__

#include "Logger.hpp"
#include "LogChannel.hpp"
#include "LogHandler.hpp"
#include "LogLevel.hpp"

#include <unordered_map>
#include <mutex>

class LogFactory
{
    protected:
        std::mutex _mutex;

        std::unordered_map<std::string,Logger*> _loggers;
        std::unordered_map<std::string,LogChannel*> _channels;
        std::unordered_map<std::string,LogHandler*> _handlers;

        LogFactory();
    public:
        inline void lock()
        {
            _mutex.lock();
        }

        inline void unlock()
        {
            _mutex.unlock();
        }
        static LogFactory& getInstance();
        static Logger& getLogger(std::string name="", LogLevel level=LogLevel::INFO);
        static LogChannel& getLogChannel(std::string name="", LogLevel level=LogLevel::INFO);
        template<class HANDLER> static LogHandler& getLogHandler(std::string name="", LogLevel level=LogLevel::INFO)
        {
            LogFactory& logFactory = getInstance();
            std::unordered_map<std::string,LogHandler*>::iterator foundChannel = logFactory._handlers.find(name);
            if (foundChannel!=logFactory._handlers.end())
            {
                return *foundChannel->second;
            }
            return *(logFactory._handlers.insert(std::make_pair(std::move(name), new HANDLER(name,level))).first)->second;
        }
        ~LogFactory();
};

//some helpers to write less code
inline Logger& logger(std::string name="", LogLevel level=LogLevel::INFO)
{
    return LogFactory::getLogger(name,level);
}
inline LogChannel& channel(std::string name="", LogLevel level=LogLevel::INFO)
{
    return LogFactory::getLogChannel(name,level);
}
template<class HANDLER> inline LogHandler& handler(std::string name="", LogLevel level=LogLevel::INFO)
{
    return LogFactory::getLogHandler<HANDLER>(name,level);
}
#endif

