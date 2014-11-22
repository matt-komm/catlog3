#include "Logger.hpp"
#include "LogFactory.hpp"

#include <cmath>
#include <iostream>
#include <time.h>

int main()
{
    Logger& root = LogFactory::get();
    
    
    float mean=0.0;
	float mean2=0.0;
	for (int run=0; run<10; ++run)
	{
		clock_t t = clock();
		for (int i = 0; i < 100000; ++i)
		{
			//int g = i*2+std::cos((i%20)*0.1);
			//g = g + g;
            root.log(LogLevel::DEBUG,"bla",125422,2342.5,true,&root,std::make_pair("testcat",32342));
        }
		t = clock() -t;
		mean+=(float)t/CLOCKS_PER_SEC;
		mean2+=(float)t*t/CLOCKS_PER_SEC/CLOCKS_PER_SEC;
	}
	printf("%5.4f +- %5.4f\n",mean/10.0,std::sqrt(mean2/10.0-mean*mean/100.0));
    return 0;
}
