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


class Logger
{
    friend class LogFactory;
    protected:
        std::string _name;
        LogLevel _level;
        std::vector<const LogChannel*> _channels;
        Logger(const std::string& name, const LogLevel& level) noexcept;

    public:
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
        inline void addLogChannel(const LogChannel& logChannel)
        {
            _channels.push_back(&logChannel);
            std::stable_sort(_channels.begin(),_channels.end(),[](const LogChannel* c1, const LogChannel* c2){return c1->level()<c2->level();});
        }

        template<class... ARGS> void log(const LogLevel& logLevel, const ARGS&... args) const
        {   
            //pass by const ref if possible? Howto?
            //std::cout<<"Logger::log"<<std::endl;

            if (logLevel>=_level && _channels.size()>0 && logLevel>=_channels[0]->level())
            {

                LogRecord logRecord(logLevel);
                //logRecord.processArguments(std::make_pair("loglevel",logLevel),std::forward<ARGS>(args)...);
                //logRecord.processArguments<typename std::add_lvalue_reference<typename std::add_const<ARGS&>::type>::type...>(args...);
                logRecord.processArguments(args...);
                //logRecord.processArguments<ARGS...>(args...);
                //this->emit(logRecord);

                /*
                for (LogRecord::CategorizedMessages::const_iterator it = logRecord._messages.cbegin(); it != logRecord._messages.cend(); ++it)
                {
                    std::cout<<"["<<it->first<<"] : ";
                    for (const std::unique_ptr<GenericType>& m: it->second)
                    {
                        std::cout<<m->format()<<" ";
                    }
                    std::cout<<std::endl;
                }
                */
            }
            //std::cout<<"Logger::log <-"<<std::endl;
        }

        void emit(const LogRecord& logRecord) const;


        //do not allow copies only moves
        Logger(const Logger& c) = delete;
        Logger(Logger&& c);
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c);
        ~Logger() noexcept;
};

#endif

