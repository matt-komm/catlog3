#ifndef __LOGFACTORY_H__
#define __LOGFACTORY_H__

#include "Logger.hpp"
#include "LogChannel.hpp"
#include "LogLevel.hpp"

#include <unordered_map>

class LogFactory
{
    protected:
        std::unordered_map<std::string,Logger> _loggers;
        std::unordered_map<std::string,LogChannel> _channels;
        LogFactory();
    public:
        static LogFactory& getInstance();
        static Logger& getLogger(std::string name="", LogLevel level=LogLevel::INFO);
        static LogChannel& getLogChannel(std::string name="", LogLevel level=LogLevel::INFO);
        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
};

#endif

