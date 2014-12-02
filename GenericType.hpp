#ifndef __GENERICTYPE_H__
#define __GENERICTYPE_H__

#include "Formatter.hpp"

#include <string>
#include <iostream>
#include <ctime>

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
            //std::cout<<"GenericTypeTmplRef::create"<<std::endl;
        }

        GenericTypeTmpl<TYPE>& operator=(const TYPE& type)
        {
            _type=type;
            return *this;
        }

        virtual std::string format() const
        {
            std::stringstream ss;
            ss<<_type;
            return std::move(ss.str());
        }

        virtual ~GenericTypeTmpl()
        {
            //std::cout<<"GenericTypeTmplRef::destroy"<<std::endl;
        }
};

template<>
class GenericTypeTmpl<std::tm>:
    public GenericType
{
    protected:
        const std::tm& _type;
    public:
        GenericTypeTmpl(const std::tm& type):
            _type(type)
        {
            //std::cout<<"GenericTypeTmplRef::create"<<std::endl;
        }

        virtual std::string format() const
        {
            std::stringstream ss;
            ss<<_type.tm_hour<<":"<<_type.tm_min<<":"<<_type.tm_sec;
            return std::move(ss.str());
        }

        virtual ~GenericTypeTmpl()
        {
            //std::cout<<"GenericTypeTmplRef::destroy"<<std::endl;
        }
};

#endif
