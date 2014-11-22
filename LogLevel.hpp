#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__

#include <string>

struct LogLevel
{
    enum LEVEL
    {
        MAXDEBUG=0,   //full debug
        DEBUG=1,      //nominal debug
        MINDEBUG=2,   //min debug
        MAXINFO=3,    //full info
        INFO=4,       //nominal info
        MININFO=5,    //min info
        FLOW=6,       //normal messages during program flow
        WARNING=7,    //only warnings, e.g. something "might" go wrong
        ERROR=8,      //only errors, e.g caught exceptions
        CRITICAL=9,   //only critical which lead to program crash
        NONE=10       //nothing

    } _level;
    
    LogLevel(LogLevel::LEVEL level):
        _level(level)
    {
    }
    
    const char* toString()
    {
        return convertLogLevel(_level);
    }

    static const char* convertLogLevel(const LogLevel::LEVEL& level)
    {
    	switch (level)
    	{
    		case LogLevel::MAXDEBUG: return "MAXDEBUG";
    		case LogLevel::DEBUG: return "DEBUG";
    		case LogLevel::MINDEBUG: return "MINDEBUG";
    		case LogLevel::MAXINFO: return "MAXINFO";
    		case LogLevel::INFO: return "INFO";
    		case LogLevel::MININFO: return "MININFO";
    		case LogLevel::FLOW: return "FLOW";
    		case LogLevel::WARNING: return "WARNING";
    		case LogLevel::ERROR: return "ERROR";
    		case LogLevel::CRITICAL: return "CRITICAL";
    		case LogLevel::NONE: return "NONE";
    		default: return "";
    	}
    	return "";
    }
};



#endif

