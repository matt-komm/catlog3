#ifndef __GENERICTYPE_H__
#define __GENERICTYPE_H__

#include "Formatter.hpp"

#include <string>

class GenericType
{
    public:
        virtual std::string format() const = 0;
    
        virtual ~GenericType()
        {
        }
        
};

template<class TYPE>
class GenericTypeTmpl:
    public GenericType
{
    protected:
        const TYPE& _type;
    public:
        GenericTypeTmpl(const TYPE& type):
            _type(type)
        {
        }
        
        virtual std::string format() const
        {
            std::stringstream ss;
            ss<<_type;
            return std::move(ss.str());
        }
    
        virtual ~GenericTypeTmpl()
        {
        }
};

#endif
