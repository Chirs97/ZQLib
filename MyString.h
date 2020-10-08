#ifndef MYSTRING_H
#define MYSTRING_H

#include "Object.h"

using namespace ZQLib;

namespace ZQLib
{

class String : public Object
{
protected:
    void Init(const char* str);

    char* m_str;
    int m_length;

public:
    String();
    String(char c);
    String(const char* str);
    String(const String& str);
    ~String();

    int Length() const;
    const char* ToCharArray() const;

    bool operator ==(const String& str) const;
    bool operator ==(const char* str) const;
    bool operator !=(const String& str) const;
    bool operator !=(const char* str) const;
    bool operator >(const String& str) const;
    bool operator >(const char* str) const;
    bool operator <(const String& str) const;
    bool operator <(const char* str) const;
    bool operator >=(const String& str) const;
    bool operator >=(const char* str) const;
    bool operator <=(const String& str) const;
    bool operator <=(const char* str) const;
    String operator +(const String& str) const;

};

}

#endif // STRING_H
