#include "Time.hpp"
#include <ctime>
#include <chrono>
#include <cstdio>

Time::Time(
        unsigned char msec,
        unsigned char sec,
        unsigned char min,
        unsigned char hour,
        unsigned char dayOfWeek,
        unsigned char dayOfMonth,
        unsigned char dayOfYear,
        unsigned char month,
        unsigned int year
    ):
        msec(msec),
        sec(sec),
        min(min),
        hour(hour),
        dayOfWeek(dayOfWeek),
        dayOfMonth(dayOfMonth),
        dayOfYear(dayOfYear),
        month(month),
        year(year)
{

}

Time Time::now()
{
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    unsigned char msec = (unsigned char)std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count()-std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count()*1000;
    std::time_t tt = std::chrono::system_clock::to_time_t(t);
    std::tm* localtime = std::localtime(&tt);
    unsigned char sec = (unsigned char)localtime->tm_sec;
    unsigned char min = (unsigned char)localtime->tm_min;
    unsigned char hour = (unsigned char)localtime->tm_hour;
    unsigned char dayOfWeek = (unsigned char)localtime->tm_wday;
    unsigned char dayOfMonth = (unsigned char)localtime->tm_mday;
    unsigned char dayOfYear = (unsigned char)localtime->tm_yday;
    unsigned char month = (unsigned char)localtime->tm_mon;
    unsigned int year = (unsigned int)localtime->tm_year+1900;

    Time time(
        msec,
        sec,
        min,
        hour,
        dayOfWeek,
        dayOfMonth,
        dayOfYear,
        month,
        year
    );
    return std::move(time);
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
    stream<<(int)time.year<<"/"<<(int)time.month<<"/"<<(int)time.dayOfMonth<<" "
          <<(int)time.hour<<":"<<(int)time.min<<":"<<(int)time.sec<<","<<(int)time.msec;
    return stream;
}


