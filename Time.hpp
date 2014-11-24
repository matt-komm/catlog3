#ifndef __TIME_H__
#define __TIME_H__

#include <utility>

class Time
{
    protected:
        Time();
        
        
    public:
        static Time now(); 
        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
};

#endif

