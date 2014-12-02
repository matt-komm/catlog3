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


        template<class... ARGS> void log(const LogLevel& logLevel, const ARGS&... args) const
        {   
            //pass by const ref if possible? Howto?
            //std::cout<<"Logger::log"<<std::endl;

            if (this->level()<=logLevel && this->accept(logLevel))
            {

                LogRecord logRecord(logLevel);
                //logRecord.processArguments(std::make_pair("loglevel",logLevel),std::forward<ARGS>(args)...);
                //logRecord.processArguments<typename std::add_lvalue_reference<typename std::add_const<ARGS&>::type>::type...>(args...);
                logRecord.processArguments(args...);
                this->propagate(logRecord);
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


        //do not allow copies only moves
        Logger(const Logger& c) = delete;
        Logger(Logger&& c);
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c);
        ~Logger() noexcept;
};

#endif

