#include "MyString.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"

using namespace std;

namespace ZQLib
{

String::String()
{
    this->Init("");
}

String::String(char c)
{
    char s[] = {c, '\0'};
    this->Init(s);
}

String::String(const char* str)
{
    this->Init(str ? str : "");
}

String::String(const String& str)
{
    this->Init(str.m_str);
}

String::~String()
{
    free(this->m_str);
}

void String::Init(const char *str)
{
    this->m_str = strdup(str);

    if(this->m_str)
    {
        m_length = strlen(this->m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String object ...");
    }
}

int String::Length() const
{
    return this->m_length;
}

const char* String::ToCharArray() const
{
    return this->m_str;
}

bool String::operator ==(const String& str) const
{
    return (strcmp(this->m_str, str.m_str) == 0);
}

bool String::operator ==(const char* str) const
{
    return (strcmp(this->m_str, str) == 0);
}

bool String::operator !=(const String& str) const
{
    return !(*this == str);
}

bool String::operator !=(const char* str) const
{
    return !(*this == str);
}

bool String::operator >(const String& str) const
{
    return (strcmp(this->m_str, str.m_str) > 0);
}

bool String::operator >(const char* str) const
{
    return (strcmp(this->m_str, str) > 0);
}

bool String::operator <(const String& str) const
{
    return (strcmp(this->m_str, str.m_str) < 0);
}

bool String::operator <(const char* str) const
{
    return (strcmp(this->m_str, str) < 0);
}

bool String::operator >=(const String& str) const
{
    return (strcmp(this->m_str, str.m_str) >= 0);
}

bool String::operator >=(const char* str) const
{
    return (strcmp(this->m_str, str) >= 0);
}

bool String::operator <=(const String& str) const
{
    return (strcmp(this->m_str, str.m_str) <= 0);
}

bool String::operator <=(const char* str) const
{
    return (strcmp(this->m_str, str) <= 0);
}

String String::operator +(const String& str) const
{

}

}

