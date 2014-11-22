#ifndef __LOGFACTORY_H__
#define __LOGFACTORY_H__

#include "Logger.hpp"
#include "LogLevel.hpp"

#include <unordered_map>

class LogFactory
{
    protected:
        std::unordered_map<std::string,Logger> _loggers;
        LogFactory();
    public:
        static LogFactory& getInstance();
        static Logger& get(std::string name="", LogLevel level=LogLevel::INFO); 
        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
};

#endif

