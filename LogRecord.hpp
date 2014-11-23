#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include "GenericType.hpp"

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>

#include <iostream>

class LogRecord
{
    protected:
        typedef std::vector<std::unique_ptr<GenericType>> MessageParts;
        typedef std::map<std::string,MessageParts> CategorizedMessages;
        CategorizedMessages _messages;
    public:
        LogRecord();
        template<class FIRST,class... ARGS> void processArguments(std::pair<const char*,FIRST> first, ARGS... args)
        {
            MessageParts& messageList = _messages[first.first];
            std::unique_ptr<GenericType> genericType(new GenericTypeTmpl<FIRST>(first.second));
            messageList.push_back(std::move(genericType));
            processArguments(std::forward<ARGS>(args)...);
        }
        template<class FIRST, class... ARGS> void processArguments(FIRST first, ARGS... args)
        {
            MessageParts& messageList = _messages[""];
            std::unique_ptr<GenericType> genericType(new GenericTypeTmpl<FIRST>(first));
            messageList.push_back(std::move(genericType));
            processArguments(std::forward<ARGS>(args)...);
        }
        
        void processArguments()
        {
            for (CategorizedMessages::const_iterator it = _messages.cbegin(); it != _messages.cend(); ++it)
            {
                std::cout<<"["<<it->first<<"] : ";
                for (const std::unique_ptr<GenericType>& m: it->second)
                {
                    std::cout<<m->format()<<" ";
                }
                std::cout<<std::endl;
            }
            
        }
        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
        
        ~LogRecord()
        {
        }
};

#endif

