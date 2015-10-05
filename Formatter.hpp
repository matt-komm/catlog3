#ifndef __FORMATTER_H__
#define __FORMATTER_H__

#include <string>
#include <sstream>
#include <typeinfo>

class Formatter
{
    protected:
    public:
    
        template<class TYPE> std::string format(const TYPE& type) const
        {
            std::stringstream ss;
            ss<<type<<" ("<<typeid(TYPE).name()<<")";
            return std::move(ss.str());
        }
        
        std::string format(const int& type) const
        {
            std::stringstream ss;
            ss<<"inter";
            return std::move(ss.str());
        }
        
};



#endif

