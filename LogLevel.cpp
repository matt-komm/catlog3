#include "LogLevel.hpp"

const std::string LogLevel::maxdebug = "MAXDEBUG";
const std::string LogLevel::debug = "DEBUG";
const std::string LogLevel::mindebug = "MINDEBUG";
const std::string LogLevel::maxinfo = "MAXINFO";
const std::string LogLevel::info = "INFO";
const std::string LogLevel::mininfo = "MININFO";
const std::string LogLevel::flow = "FLOW";
const std::string LogLevel::warning = "WARNING";
const std::string LogLevel::error = "ERROR";
const std::string LogLevel::critical = "CRITICAL";
const std::string LogLevel::none = "NONE";

std::ostream& operator<<(std::ostream& stream, const LogLevel& logLevel)
{
    stream<<logLevel.toString();
    return stream;
}
