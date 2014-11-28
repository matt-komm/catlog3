#ifndef __LOGFACTORY_H__
#define __LOGFACTORY_H__

#include "Logger.hpp"
#include "LogChannel.hpp"
#include "LogHandler.hpp"
#include "LogLevel.hpp"

#include <unordered_map>

class LogFactory
{
    protected:
        std::unordered_map<std::string,Logger*> _loggers;
        std::unordered_map<std::string,LogChannel*> _channels;
        std::unordered_map<std::string,LogHandler*> _handlers;
        LogFactory();
    public:
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
        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
};

#endif

