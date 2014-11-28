#ifndef __LOGCHANNEL_H__
#define __LOGCHANNEL_H__

#include "LogRecord.hpp"
#include "LogLevel.hpp"

#include <vector>
#include <string>
#include <algorithm>


class LogChannel
{
    friend class LogFactory;
    friend class Logger;
    friend class LogHandler;

    protected:
        std::string _name;
        LogLevel _level;

        std::vector<const LogChannel*> _channels;

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
        inline const LogLevel& effectiveLevel() const
        {
            if (_channels.size()>0)
            {
                const LogLevel& channelLogLevel = _channels.front()->effectiveLevel();

                //record need to be higher than level to get processed
                //if that is passed it counts if the channels would pick it up
                return channelLogLevel<_level ? _level : channelLogLevel;
            }
            else
            {
                return _level;
            }
        }
        inline void setLogLevel(const LogLevel& logLevel)
        {
            _level=logLevel;
        }

        inline void addLogChannel(const LogChannel& channel)
        {
            _channels.push_back(&channel);
            std::stable_sort(_channels.begin(),_channels.end(),[](const LogChannel* c1, const LogChannel* c2){return c1->level()<c2->level();});
        }

        virtual void propagate(const LogRecord& logRecord) const;

        virtual ~LogChannel() noexcept;
};

#endif

