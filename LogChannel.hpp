#ifndef __LOGCHANNEL_H__
#define __LOGCHANNEL_H__

#include "LogHandler.hpp"
#include "LogRecord.hpp"
#include "LogLevel.hpp"

#include <vector>
#include <string>


class LogChannel
{
    friend class LogFactory;
    protected:
        std::string _name;
        LogLevel _level;

        std::vector<LogHandler*> _handlers;

        LogChannel(const std::string& name, const LogLevel& level) noexcept;
    public:


        LogChannel(const LogChannel& logChannel) = delete;
        LogChannel(LogChannel&& logChannel);
        LogChannel& operator=(const LogChannel& logChannel) = delete;
        LogChannel& operator=(LogChannel&& logChannel);
        inline const std::string& name() const
        {
            return _name;
        }
        inline const LogLevel& level() const
        {
            return _level;
        }
        inline void setLogLevel(const LogLevel& logLevel)
        {
            _level=logLevel;
        }


        void propagate(const LogRecord& logRecord) const;

        ~LogChannel() noexcept;
};

#endif

