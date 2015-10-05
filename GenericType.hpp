#ifndef __GENERICTYPE_H__
#define __GENERICTYPE_H__

#include "Formatter.hpp"

#include <string>
#include <iostream>
#include <ctime>

class GenericType
{
    public:
        virtual std::string format(const Formatter& formatter) const = 0;
    
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

        GenericTypeTmpl<TYPE>& operator=(const TYPE& type)
        {
            _type=type;
            return *this;
        }

        virtual std::string format(const Formatter& formatter) const
        {
            return std::move(formatter.format(_type));
        }

        virtual ~GenericTypeTmpl()
        {
        }
};


#endif
