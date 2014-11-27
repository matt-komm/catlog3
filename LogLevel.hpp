#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__

#include <string>

class LogLevel
{
    private:
        static const std::string maxdebug;
        static const std::string debug;
        static const std::string mindebug;
        static const std::string maxinfo;
        static const std::string info;
        static const std::string mininfo;
        static const std::string flow;
        static const std::string warning;
        static const std::string error;
        static const std::string critical;
        static const std::string none;
    public:
    
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

        LogLevel(const LogLevel& logLevel) = default;
        LogLevel(LogLevel&& logLevel) = default;
        LogLevel& operator=(const LogLevel& logLevel) = default;
        LogLevel& operator=(LogLevel&& logLevel) = default;

        const std::string toString() const
        {
            return convertLogLevel(_level);
        }

        inline bool operator<=(const LogLevel& logLevel) const
        {
            return _level<=logLevel._level;
        }
        inline bool operator>=(const LogLevel& logLevel) const
        {
            return _level>=logLevel._level;
        }
        inline bool operator<(const LogLevel& logLevel) const
        {
            return _level<logLevel._level;
        }
        inline bool operator>(const LogLevel& logLevel) const
        {
            return _level>logLevel._level;
        }
        inline bool operator==(const LogLevel& logLevel) const
        {
            return _level==logLevel._level;
        }
        inline bool operator!=(const LogLevel& logLevel) const
        {
            return _level!=logLevel._level;
        }
    
        static const std::string convertLogLevel(const LogLevel::LEVEL& level)
        {
            switch (level)
            {
                case LogLevel::MAXDEBUG: return maxdebug;
                case LogLevel::DEBUG: return debug;
                case LogLevel::MINDEBUG: return mindebug;
                case LogLevel::MAXINFO: return maxinfo;
                case LogLevel::INFO: return info;
                case LogLevel::MININFO: return mininfo;
                case LogLevel::FLOW: return flow;
                case LogLevel::WARNING: return warning;
                case LogLevel::ERROR: return error;
                case LogLevel::CRITICAL: return critical;
                case LogLevel::NONE: return none;
                default: return "";
            }
            return "";
        }
};

std::ostream& operator<<(std::ostream& stream, const LogLevel& logLevel);

#endif

