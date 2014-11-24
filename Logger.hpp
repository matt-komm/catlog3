#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevel.hpp"
#include "LogRecord.hpp"
#include "GenericType.hpp"

#include <string>

#include <iostream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>


class Logger
{
    friend class LogFactory;
    protected:
        std::string _name;
        LogLevel _level;
        Logger* _parent;
        Logger(std::string name, LogLevel level) noexcept;
        
    public:
        template<class... ARGS> void log(const LogLevel& logLevel, const ARGS&... args) const
        {   
            //pass by const ref if possible? Howto?
            //std::cout<<"Logger::log"<<std::endl;

            if (logLevel._level>=_level._level)
            {
                LogRecord logRecord;
                //logRecord.processArguments(std::make_pair("loglevel",logLevel),std::forward<ARGS>(args)...);
                //logRecord.processArguments<typename std::add_lvalue_reference<typename std::add_const<ARGS&>::type>::type...>(args...);
                logRecord.processArguments(args...);
                //logRecord.processArguments<ARGS...>(args...);
                this->emit(logRecord);

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



                if (_parent!=nullptr)
                {
                    _parent->emit(logRecord);
                }
            }
            //std::cout<<"Logger::log <-"<<std::endl;
        }
        
        void emit(const LogRecord& logRecord) const
        {
            //std::cout<<"Logger::emit"<<std::endl;
            for (LogRecord::CategorizedMessages::const_iterator it = logRecord._messages.cbegin(); it != logRecord._messages.cend(); ++it)
            {
                std::cout<<"["<<it->first<<"] : ";
                for (const std::unique_ptr<GenericType>& m: it->second)
                {
                    std::cout<<m->format()<<" ";
                }
                std::cout<<std::endl;
            }
        }
        //do not allow copies only moves
        Logger(const Logger& c) = delete;
        Logger(Logger&& c);
        Logger& operator=(const Logger& c) = delete;
        Logger& operator=(Logger&& c);
        ~Logger() noexcept
        {
        }
        
};

#endif

