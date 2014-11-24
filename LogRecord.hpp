#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include "GenericType.hpp"

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
        typedef std::vector<std::unique_ptr<GenericType>> MessageParts;
        typedef std::map<std::string,MessageParts> CategorizedMessages;
    public:
        CategorizedMessages _messages;
    public:
        LogRecord();
        template<class MESSAGE,class... ARGS> void processArguments(const std::pair<const char*,MESSAGE>& pairedMessage, const ARGS&... args)
        {
            ///std::cout<<pairedMessage.first<<","<<pairedMessage.second<<std::endl;
            MessageParts& messageList = _messages[pairedMessage.first];
            GenericTypeTmpl<MESSAGE>* genericType = new GenericTypeTmpl<MESSAGE>(pairedMessage.second);
            messageList.emplace_back(genericType);
            processArguments(args...);
        }
        template<class MESSAGE, class... ARGS> void processArguments(const MESSAGE& message, const ARGS&... args)
        {
            //std::cout<<"LogRecord::processArguments<...>(...)"<<std::endl;

            MessageParts& messageList = _messages[""];
            GenericTypeTmpl<MESSAGE>* genericType = new GenericTypeTmpl<MESSAGE>(message);
            messageList.emplace_back(genericType);
            processArguments(args...);
            //std::cout<<"LogRecord::processArguments<...>(...) <-"<<std::endl;
        }
        
        void processArguments()
        {
            //std::cout<<"LogRecord::processArguments<>()"<<std::endl;
            /*
            for (CategorizedMessages::const_iterator it = _messages.cbegin(); it != _messages.cend(); ++it)
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

        inline const CategorizedMessages& getMessages() const
        {
            return _messages;
        }

        LogRecord(const LogRecord& logRecord) = delete;
        LogRecord(LogRecord&& logRecord):
            _messages(std::move(logRecord._messages))
        {

        }
        LogRecord& operator=(const LogRecord& logRecord) = delete;
        LogRecord& operator=(LogRecord&& logRecord)
        {
            _messages=std::move(logRecord._messages);
            return *this;
        }
        
        ~LogRecord()
        {
        }
};

#endif

