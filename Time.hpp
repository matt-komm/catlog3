#ifndef __TIME_H__
#define __TIME_H__

#include <utility>
#include <bitset>
#include <iostream>

class Time
{
    protected:
        Time(
            unsigned char msec,
            unsigned char sec,
            unsigned char min,
            unsigned char hour,
            unsigned char dayOfWeek,
            unsigned char dayOfMonth,
            unsigned char dayOfYear,
            unsigned char month,
            unsigned int year
        );
        
        
    public:
        const unsigned char msec;
        const unsigned char sec;
        const unsigned char min;
        const unsigned char hour;
        const unsigned char dayOfWeek;
        const unsigned char dayOfMonth;
        const unsigned char dayOfYear;
        const unsigned char month;
        const unsigned int year;

        static Time now(); 

        /*
        Class(const Class& c);
        Class(Class&& c);
        Class& operator=(const Class& c);
        Class& operator=(Class&& c);
        ~Class();
        */
};

std::ostream& operator<<(std::ostream& stream, const Time& time);

#endif

