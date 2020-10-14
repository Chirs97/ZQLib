#ifndef ZSTRING_H
#define ZSTRING_H

#include "Object.h"

using namespace ZQLib;

namespace ZQLib
{

class ZString : public Object
{
protected:
    void Init(const char* str);
    bool Equal(const char* l, const char* r, int len) const;

    static int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);

    char* m_str;
    int m_length;

public:
    ZString();
    ZString(char c);
    ZString(const char* str);
    ZString(const ZString& str);
    ~ZString();

    int Length() const;
    const char* ToCharArray() const;
    bool StartWith(const char* str) const;
    bool StartWith(const ZString& str) const;
    bool EndOf(const char* str) const;
    bool EndOf(const ZString& str) const;
    ZString& Insert(int index, const char* str);
    ZString& Insert(int index, const ZString& str);
    ZString& Trim();
    int IndexOf(const char* str) const;
    int IndexOf(const ZString& str) const;
    ZString& Remove(int index, int len);
    ZString& Remove(const char* str);
    ZString& Remove(const ZString& str);
    ZString& Replace(const char* t, const char* s);
    ZString& Replace(const ZString& t, const char* s);
    ZString& Replace(const char *t, const ZString& s);
    ZString& Replace(const ZString& t, const ZString& s);
    ZString SubString(int index, int len) const;

    char& operator[](int index);
    char operator[](int index) const;
    bool operator ==(const ZString& str) const;
    bool operator ==(const char* str) const;
    bool operator !=(const ZString& str) const;
    bool operator !=(const char* str) const;
    bool operator >(const ZString& str) const;
    bool operator >(const char* str) const;
    bool operator <(const ZString& str) const;
    bool operator <(const char* str) const;
    bool operator >=(const ZString& str) const;
    bool operator >=(const char* str) const;
    bool operator <=(const ZString& str) const;
    bool operator <=(const char* str) const;

    ZString operator +(const ZString& str) const;
    ZString operator +(const char* str) const;
    ZString& operator +=(const ZString& str);
    ZString& operator +=(const char* str);

    ZString operator -(const ZString& str) const;
    ZString operator -(const char* str) const;
    ZString& operator -=(const ZString& str);
    ZString& operator -=(const char* str);

    ZString& operator =(const ZString& str);
    ZString& operator =(const char* str);
    ZString& operator =(char c);


};

}

#endif // ZSTRING_H
