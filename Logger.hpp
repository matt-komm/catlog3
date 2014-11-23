#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevel.hpp"
#include "LogRecord.hpp"

#include <string>

#include <iostream>
#include <utility>


class Logger
{
    friend class LogFactory;
    protected:
        std::string _name;
        LogLevel _level;
        Logger(std::string name, LogLevel level);
        
    public:
        template<class... ARGS> void log(const LogLevel& logLevel, const ARGS&... args)
        {   
            if (logLevel._level>=_level._level)
            {
                LogRecord logRecord;
                logRecord.processArguments(std::make_pair("loglevel",logLevel),std::forward<const ARGS&>(args)...);
            }

        }
        
        //do not allow copies only moves
        Logger(const Logger& c) = delete;
        Logger(Logger&& c);
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c);
        ~Logger()
        {
        }
        
};

#endif

