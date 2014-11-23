#include "Logger.hpp"
#include "LogFactory.hpp"

#include <cmath>
#include <iostream>
#include <time.h>

#define LOG(logger, level, msg...) \
    logger.log(level,msg , std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__))

template<class... ARGS> void measure(Logger& logger, const char* name, ARGS... args)
{
    float mean=0.0;
	float mean2=0.0;
	const int acuracy=20;
	for (int run=0; run<acuracy; ++run)
	{
		clock_t t = clock();
		for (int i = 0; i < 10000; ++i)
		{
			//int g = i*2+std::cos((i%20)*0.1);
			//g = g + g;
            //root.log(LogLevel::INFO,"bla",125422,2342.5,true,&root,std::make_pair("testcat",32342));
            logger.log(LogLevel::INFO,args...);
        }
		t = clock() -t;
		mean+=(float)t/CLOCKS_PER_SEC;
		mean2+=(float)t*t/CLOCKS_PER_SEC/CLOCKS_PER_SEC;
	}
	printf("%s: \t%5.4f +- %5.4f\n",name,mean/acuracy,std::sqrt(mean2/acuracy-mean*mean/acuracy/acuracy));
}

int main()
{
    Logger& root = LogFactory::get();
    LOG(root,LogLevel::INFO,"test",342342);
    root.log(LogLevel::INFO,"test",32342,std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__));
    //std::cout<<LogLevel(LogLevel::INFO)<<std::endl;
    /*
    
    measure(root,"string1","abcdefg");
    measure(root,"string2","abcdefg","abcdefg");
    measure(root,"string3","abcdefg","abcdefg","abcdefg");
	
	measure(root,"int1",123456);
    measure(root,"int2",123456,123456);
    measure(root,"int3",123456,123456,123456);
    
	measure(root,"long1",123456l);
    measure(root,"long2",123456l,123456l);
    measure(root,"long3",123456l,123456l,123456l);
    
	measure(root,"float1",12345.6f);
    measure(root,"float2",12345.6f,12345.6f);
    measure(root,"float3",12345.6f,12345.6f,12345.6f);
    
	measure(root,"double1",12345.6);
    measure(root,"double2",12345.6,12345.6);
    measure(root,"double3",12345.6,12345.6,12345.6);
    
	measure(root,"pointer1",&root);
    measure(root,"pointer2",&root,&root);
    measure(root,"pointer3",&root,&root,&root);    
    
 	measure(root,"bool1",true);
    measure(root,"bool2",true,true);
    measure(root,"bool3",true,true,true);    
    
 	measure(root,"bool1",true);
    measure(root,"bool2",true,true);
    measure(root,"bool3",true,true,true);     
    
	measure(root,"info1",std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__));
    measure(root,"info2",std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__),std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__));
    measure(root,"info3",std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__),std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__),std::make_pair("lno",__LINE__),std::make_pair("file",__FILE__));   
    */
    
    return 0;
}
