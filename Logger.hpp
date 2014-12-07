#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevel.hpp"
#include "LogRecord.hpp"
#include "GenericType.hpp"

#include "LogChannel.hpp"

#include <string>

#include <iostream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>
#include <algorithm>


class Logger:
    public LogChannel
{
    friend class LogFactory;
    protected:
        Logger(const std::string& name, const LogLevel& level) noexcept;

    public:
        template<class... ARGS> void maxdebug(const ARGS&... args) const
        {
            this->log(LogLevel::MAXDEBUG,args...);
        }
        template<class... ARGS> void debug(const ARGS&... args) const
        {
            this->log(LogLevel::DEBUG,args...);
        }
        template<class... ARGS> void mindebug(const ARGS&... args) const
        {
            this->log(LogLevel::MINDEBUG,args...);
        }
        template<class... ARGS> void maxinfo(const ARGS&... args) const
        {
            this->log(LogLevel::MAXINFO,args...);
        }
        template<class... ARGS> void info(const ARGS&... args) const
        {
            this->log(LogLevel::INFO,args...);
        }
        template<class... ARGS> void mininfo(const ARGS&... args) const
        {
            this->log(LogLevel::MININFO,args...);
        }
        template<class... ARGS> void flow(const ARGS&... args) const
        {
            this->log(LogLevel::FLOW,args...);
        }
        template<class... ARGS> void warning(const ARGS&... args) const
        {
            this->log(LogLevel::WARNING,args...);
        }
        template<class... ARGS> void error(const ARGS&... args) const
        {
            this->log(LogLevel::ERROR,args...);
        }
        template<class... ARGS> void critical(const ARGS&... args) const
        {
            this->log(LogLevel::CRITICAL,args...);
        }
        template<class... ARGS> void log(const LogLevel& logLevel, const ARGS&... args) const
        {   
            if (this->level()<=logLevel && this->accept(logLevel))
            {
                LogRecord logRecord(logLevel);
                logRecord.processArguments(args...);
                this->propagate(logRecord);
            }
        }

        Logger(const Logger& c) = delete;
        Logger(Logger&& c);
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c);
        ~Logger() noexcept;
};

#endif

