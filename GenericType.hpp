#ifndef __GENERICTYPE_H__
#define __GENERICTYPE_H__

struct GenericType
{

    union DATA 
    {
        const char* str;
        const int* integer;
        const double* floating;
        const bool* boolean;
        const void* ptr;
    } _data;
    const char* _category;
    enum TYPE {STRING,INTEGER,FLOATING,BOOLEAN,PTR} _type;

    GenericType(const char* message, const char* category="message"):
        _category(category),
        _type(STRING)
    {
        _data.str=(message);
    }
    
    GenericType(const int& message, const char* category="message"):
        _category(category),
        _type(INTEGER)
    {
        _data.integer=(&message);
    }
    
    GenericType(const double& message, const char* category="message"):
        _category(category),
        _type(FLOATING)
    {
        _data.floating=(&message);
    }
    
    GenericType(const bool& message, const char* category="message"):
        _category(category),
        _type(BOOLEAN)
    {
        _data.boolean=(&message);
    }
    
    GenericType(const void* message, const char* category="message"):
        _category(category),
        _type(PTR)
    {
        _data.ptr=(message);
    }
};

#endif
