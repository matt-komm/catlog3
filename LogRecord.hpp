#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include "GenericType.hpp"
#include "LogLevel.hpp"
#include "Time.hpp"

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <type_traits>
#include <iostream>
#include <functional>
#include <thread>

struct LogRecordInfo
{
    const GenericTypeTmpl<Time> timeStamp;
    const GenericTypeTmpl<std::thread::id> threadId;
    
    LogRecordInfo():
        timeStamp(Time::now()),
        threadId(std::this_thread::get_id())
    {
    }
};

class Logger;

class LogRecord
{
    public:
        typedef std::reference_wrapper<const GenericType> MessagePart;
        typedef std::vector<MessagePart> MessageParts;
        typedef std::map<std::string,MessageParts> CategorizedMessages;
        typedef std::pair<std::string,MessageParts> Message;

    protected:
        CategorizedMessages _messages;

        LogRecordInfo _info;
        const Logger* _logger;
        LogLevel _level;

    public:
        inline const LogLevel& level() const
        {
            return _level;
        }
        inline const LogRecordInfo& info() const
        {
            return _info;
        }

        LogRecord(const Logger* logger, const LogLevel& level);
        
        template<class MESSAGE,class... ARGS> inline void processAndPropagate(const std::pair<const char*,MESSAGE>& pairedMessage, const ARGS&... args)
        {
            MessageParts& messageList = _messages[pairedMessage.first];
            GenericTypeTmpl<MESSAGE> genericType(pairedMessage.second);
            messageList.emplace_back(genericType);
            processAndPropagate(args...);
        }
        
        template<class MESSAGE, class... ARGS> inline void processAndPropagate(const MESSAGE& message, const ARGS&... args)
        {
            const GenericTypeTmpl<MESSAGE> genericType(message);
            _messages[""].emplace_back(genericType);
            processAndPropagate(args...);
        }
        
        void processAndPropagate();

        inline const CategorizedMessages& getMessages() const
        {
            return _messages;
        }

        LogRecord(const LogRecord& logRecord) = delete;
        LogRecord(LogRecord&& logRecord):
            _messages(std::move(logRecord._messages)),
            _level(std::move(logRecord._level))
        {

        }
        LogRecord& operator=(const LogRecord& logRecord) = delete;
        LogRecord& operator=(LogRecord&& logRecord)
        {
            _level=std::move(logRecord._level);
            _messages=std::move(logRecord._messages);
            return *this;
        }
        
        ~LogRecord()
        {
        }
};

#endif

