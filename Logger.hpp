#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevel.hpp"

#include <string>

#include <iostream>
#include <sstream>
#include <tuple>

class Logger
{
    friend class LogFactory;
    protected:
        std::string _name;
        LogLevel _level;
        Logger(std::string name, LogLevel level);
        
        std::stringstream ss;
        template<class FIRST,class... ARGS> void processArguments(std::pair<const char*,FIRST> first, ARGS... args)
        {
            ss<<"("<<first.first<<") "<<first.second<<", ";
            processArguments(args...);
        }
        template<class FIRST, class... ARGS> void processArguments(FIRST first, ARGS... args)
        {
            ss<<first<<", ";
            processArguments(args...);
        }
        
        void processArguments()
        {
            ss<<std::endl;
            ss.clear();
        }
    public:
        template<class... ARGS> void log(const LogLevel& logLevel, ARGS... args)
        {   
            if (logLevel._level>=_level._level)
            {
                ss<<logLevel.toString()<<": ";
                processArguments(args...);
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

