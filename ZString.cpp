#include "ZString.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"

using namespace std;

namespace ZQLib
{

int* ZString::make_pmt(const char* p)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if(ret != NULL)
    {
        int ll = 0;
        ret[0] = 0;
        for(int i = 1; i < len; i++)
        {
            while((ll>0) && (p[ll] != p[i]))
            {
                ll = ret[ll-1];
            }
            if(p[ll] == p[i])
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int ZString::kmp(const char* s, const char* p)
{
    int ret = -1;

    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);

    if( (pmt != NULL) && (pl > 0) && (pl <= sl))
    {
        for(int i = 0, j = 0; i < sl; i++)
        {
            while((j > 0) && (s[i] != p[j]))
            {
                j = pmt[j-1];
            }

            if(s[i] == p[j])
            {
                j++;
            }

            if(j == pl)
            {
                ret = i + 1 - pl;
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

ZString::ZString()
{
    this->Init("");
}

ZString::ZString(char c)
{
    char s[] = {c, '\0'};
    this->Init(s);
}

ZString::ZString(const char* str)
{
    this->Init(str ? str : "");
}

ZString::ZString(const ZString& str)
{
    this->Init(str.m_str);
}

ZString::~ZString()
{
    free(this->m_str);
}

void ZString::Init(const char *str)
{
    this->m_str = strdup(str);

    if(this->m_str)
    {
        m_length = strlen(this->m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ZString object ...");
    }
}

bool ZString::Equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for(int i = 0; i < len && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

int ZString::Length() const
{
    return this->m_length;
}

const char* ZString::ToCharArray() const
{
    return this->m_str;
}

bool ZString::StartWith(const char* str) const
{
    bool ret = (str != NULL);

    if(ret)
    {
        int len = strlen(str);

        ret = (len < this->m_length) && Equal(this->m_str, str, len);
    }

    return ret;
}

bool ZString::StartWith(const ZString& str) const
{
    return this->StartWith(str.m_str);
}

bool ZString::EndOf(const char* str) const
{
    bool ret = (str != NULL);

    if(ret)
    {
        int len = strlen(str);
        char* temp = this->m_str + (m_length - len);

        ret = (len < this->m_length) && Equal(temp, str, len);
    }

    return ret;
}

bool ZString::EndOf(const ZString& str) const
{
    return this->EndOf(str.m_str);
}

ZString& ZString::Insert(int index, const char* str)
{
    if((index >= 0) && (index <= this->m_length))
    {
        if((str != NULL) && (str[0] != '\0'))
        {
            int len = strlen(str);
            char* temp = reinterpret_cast<char*>(malloc(this->m_length + len + 1));

            if(temp != NULL)
            {
                strncpy(temp, this->m_str, index);
                strncpy(temp + index, str, len);
                strncpy(temp + index + len, this->m_str + index, this->m_length - index);

                temp[this->m_length + len] = '\0';

                free(this->m_str);

                this->m_str = temp;
                this->m_length = this->m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert ZString value");
            }
        }
    }

    return *this;
}

ZString& ZString::Insert(int index, const ZString& str)
{
    return this->Insert(index, str.m_str);
}

ZString& ZString::Trim()
{
    int b = 0;
    int e = this->m_length - 1;

    while(this->m_str[b] == ' ')
    {
        b++;
    }
    while(this->m_str[e] == ' ')
    {
        e--;
    }

    if(b==0)
    {
        this->m_str[e+1] = '\0';
        this->m_length = e+1;
    }
    else
    {
        for(int i = 0, j = b ; j <= e; i++, j++)
        {
            this->m_str[i] = this->m_str[j];
        }

        this->m_str[e-b+1] = '\0';
        this->m_length = e - b + 1;
    }

    return *this;
}

int ZString::IndexOf(const char* str) const
{
    return kmp(this->m_str, str ? str : "");
}

int ZString::IndexOf(const ZString& str) const
{
    return kmp(this->m_str, str.m_str);
}

ZString& ZString::Remove(int index, int len)
{
    if((index >= 0) && (index < this->m_length))
    {
        int n = index;
        int m = index + len;

        while((n < m) && (m < this->m_length))
        {
            this->m_str[n++] = this->m_str[m++];
        }
        this->m_str[n] = '\0';
        this->m_length = n;
    }

    return *this;
}

ZString& ZString::Remove(const char* str)
{
    return this->Remove(this->IndexOf(str), str ? strlen(str) : 0);
}

ZString& ZString::Remove(const ZString& str)
{
    return this->Remove(str.m_str);
}

ZString& ZString::Replace(const char* t, const char* s)
{
    if((t != NULL) && (s != NULL))
    {
        int index = this->IndexOf(t);
        if(index >= 0)
        {
            this->Remove(t);
            this->Insert(index, s);
        }
    }

    return *this;
}

ZString& ZString::Replace(const ZString& t, const char* s)
{
    return this->Replace(t.m_str, s);
}

ZString& ZString::Replace(const char *t, const ZString& s)
{
    return this->Replace(t, s.m_str);
}

ZString& ZString::Replace(const ZString& t, const ZString& s)
{
    return this->Replace(t.m_str, s.m_str);
}

ZString ZString::SubString(int index, int len) const
{
    ZString ret;

    if((index >= 0) && (index <= this->m_length))
    {
        if(len < 0)
        {
            len = 0;
        }
        if(len+index > this->m_length)
        {
            len = this->m_length - index;
        }

        char* temp = reinterpret_cast<char*>(malloc(len + 1));

        strncpy(temp, this->m_str + index, len);
        temp[len] = '\0';
        ret = temp;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
    }

    return ret;
}

char& ZString::operator[](int index)
{
    if((index >= 0) && (index < this->m_length))
    {
        return this->m_str[index];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
    }
}

char ZString::operator[](int index) const
{
    return (const_cast<ZString&>(*this))[index];
}

bool ZString::operator ==(const ZString& str) const
{
    return (strcmp(this->m_str, str.m_str) == 0);
}

bool ZString::operator ==(const char* str) const
{
    return (strcmp(this->m_str, str) == 0);
}

bool ZString::operator !=(const ZString& str) const
{
    return !(*this == str);
}

bool ZString::operator !=(const char* str) const
{
    return !(*this == str);
}

bool ZString::operator >(const ZString& str) const
{
    return (strcmp(this->m_str, str.m_str) > 0);
}

bool ZString::operator >(const char* str) const
{
    return (strcmp(this->m_str, str) > 0);
}

bool ZString::operator <(const ZString& str) const
{
    return (strcmp(this->m_str, str.m_str) < 0);
}

bool ZString::operator <(const char* str) const
{
    return (strcmp(this->m_str, str) < 0);
}

bool ZString::operator >=(const ZString& str) const
{
    return (strcmp(this->m_str, str.m_str) >= 0);
}

bool ZString::operator >=(const char* str) const
{
    return (strcmp(this->m_str, str) >= 0);
}

bool ZString::operator <=(const ZString& str) const
{
    return (strcmp(this->m_str, str.m_str) <= 0);
}

bool ZString::operator <=(const char* str) const
{
    return (strcmp(this->m_str, str) <= 0);
}

ZString ZString::operator +(const ZString& str) const
{
    return (*this + str.m_str);
}

ZString ZString::operator +(const char* str) const
{
    ZString ret;

    int len = this->m_length + strlen(str ? str : "");
    char* temp = reinterpret_cast<char*>(malloc(len + 1));

    if(temp)
    {
        strcpy(temp, m_str);
        strcat(temp, str ? str : "");

        free(ret.m_str);

        ret.m_str = temp;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add ZString value ....");
    }

    return ret;
}

ZString& ZString::operator +=(const ZString& str)
{
    return (*this = *this + str.m_str);
}

ZString& ZString::operator +=(const char* str)
{
    return (*this = *this + str);
}

ZString ZString::operator -(const ZString& str) const
{
    return ZString(*this).Remove(str);
}

ZString ZString::operator -(const char* str) const
{
    return ZString(*this).Remove(str);
}

ZString& ZString::operator -=(const ZString& str)
{
    return this->Remove(str);
}

ZString& ZString::operator -=(const char* str)
{
    return this->Remove(str);
}

ZString& ZString::operator =(const ZString& str)
{
    return (*this = str.m_str);
}

ZString& ZString::operator =(const char* str)
{
    if(this->m_str != str)
    {
        char* temp = strdup(str ? str : "");
        if(temp)
        {
            free(this->m_str);

            this->m_str = temp;
            this->m_length = strlen(this->m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new ZString value ...");
        }
    }

    return *this;
}

ZString& ZString::operator =(char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

}

