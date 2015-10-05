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

        inline unsigned int nChannels() const
        {
            return _channels.size();
        }

        virtual bool accept(const LogLevel& level) const
        {
            for (unsigned int ichannel=0; ichannel<_channels.size(); ++ichannel)
            {
                if (_channels[ichannel]->level()>level)
                {
                    break;
                }
                if (_channels[ichannel]->accept(level))
                {
                    return true;
                }
            }
            return false;
        }

        inline const LogLevel& level() const
        {
            return _level;
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

        LogChannel& operator>>(LogChannel& logChannel)
        {
            this->addLogChannel(logChannel);
            return logChannel;
        }

        virtual void propagate(const LogRecord& logRecord) const;
        virtual void emit(const LogLevel& level) const;

        virtual ~LogChannel() noexcept;
};

#endif

