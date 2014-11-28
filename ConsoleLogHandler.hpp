#ifndef __CONSOLELOGHANDLER_H__
#define __CONSOLELOGHANDLER_H__

#include "LogFactory.hpp"
#include "LogHandler.hpp"
#include "LogLevel.hpp"
#include "GenericType.hpp"

#include <sstream>
#include <iostream>

class ConsoleLogHandler:
    public LogHandler
{
    protected:
    public:
        ConsoleLogHandler(const std::string& name, const LogLevel& level):
            LogHandler(name,level)
        {

        }
        virtual void handle(const LogRecord& logRecord) const
        {
            std::stringstream ss;
            const LogRecord::CategorizedMessages& catmsg = logRecord.getMessages();
            for (LogRecord::CategorizedMessages::const_iterator it = catmsg.cbegin(); it != catmsg.cend(); ++it)
            {
                ss<<"["<<it->first<<"] ";

                for (LogRecord::MessageParts::const_iterator m = it->second.cbegin(); m != it->second.cend(); ++m)
                {
                    //ss<<m->format()<<" ";
                }

                ss<<std::endl;
            }
            //std::cout<<ss.str().c_str();

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

