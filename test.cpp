#include "Logger.hpp"
#include "LogFactory.hpp"

int main()
{
    Logger& root = LogFactory::get();
    root.log(LogLevel::INFO,"bla",125422,2342.5,true,&root,std::make_pair("testcat",32342));
    return 0;
}
