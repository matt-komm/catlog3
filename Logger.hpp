#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevel.hpp"

#include <string>

#include <iostream>


class Logger
{
    friend class LogFactory;
    protected:
        std::string _name;
        Logger(std::string name);
        template<class FIRST,class... ARGS> void processArguments(std::pair<const char*,FIRST> first, ARGS... args)
        {
            std::cout<<"("<<first.first<<") "<<first.second<<", ";
            processArguments(args...);
        }
        template<class FIRST, class... ARGS> void processArguments(FIRST first, ARGS... args)
        {
            std::cout<<first<<", ";
            processArguments(args...);
        }
        
        void processArguments()
        {
            std::cout<<std::endl;
        }
    public:
        template<class... ARGS> void log(LogLevel logLevel, ARGS... args)
        {
            std::cout<<logLevel.toString()<<": ";
            processArguments(args...);
        }
        
        //do not allow copies only moves
        Logger(const Logger& c) = delete;
        Logger(Logger&& c) =default;
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c)=default;
        ~Logger()
        {
        }
        
};

#endif

