#ifndef __LOGHANDLER_H__
#define __LOGHANDLER_H__

#include "LogLevel.hpp"
#include "LogChannel.hpp"
#include "LogRecord.hpp"

class LogHandler:
    public LogChannel
{
    friend class LogFactory;

    protected:
        LogHandler(const std::string& name, const LogLevel& level);
    public:
        virtual void handle(const LogRecord& logRecord) const = 0;
        virtual void propagate(const LogRecord& logRecord) const
        {
            if (this->level()<=logRecord.level())
            {
                this->handle(logRecord);
            }
            LogChannel::propagate(logRecord);
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

