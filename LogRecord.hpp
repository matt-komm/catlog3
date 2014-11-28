#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include "GenericType.hpp"
#include "LogLevel.hpp"

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <type_traits>
#include <iostream>

class LogRecord
{
    public:
        typedef std::unique_ptr<GenericType> MessagePart;
        typedef std::vector<MessagePart> MessageParts;
        typedef std::map<std::string,MessageParts> CategorizedMessages;
        typedef std::pair<std::string,MessageParts> Message;

    protected:
        CategorizedMessages _messages;
        LogLevel _level;
    public:
        inline const LogLevel& level() const
        {
            return _level;
        }

        LogRecord(const LogLevel& level);
        template<class MESSAGE,class... ARGS> void processArguments(const std::pair<const char*,MESSAGE>& pairedMessage, const ARGS&... args)
        {
            MessageParts& messageList = _messages[pairedMessage.first];
            GenericTypeTmpl<MESSAGE>* genericType = new GenericTypeTmpl<MESSAGE>(pairedMessage.second);
            messageList.emplace_back(genericType);
            processArguments(args...);
        }
        template<class MESSAGE, class... ARGS> void processArguments(const MESSAGE& message, const ARGS&... args)
        {
            MessageParts& messageList = _messages[""];
            GenericTypeTmpl<MESSAGE>* genericType = new GenericTypeTmpl<MESSAGE>(message);
            messageList.emplace_back(genericType);
            processArguments(args...);
        }
        
        void processArguments()
        {
        }

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

