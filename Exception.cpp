#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace ZQLib
{

Exception::Exception()
{
    this->m_message = NULL;
    this->m_location = NULL;
}

Exception::Exception(const char *message, const char* file, int line) : Exception()
{
    this->m_message = (this->m_message ? strdup(message) : NULL);

    if(file != NULL)
    {
        char sl[16] = {0};
        itoa(line,sl,10);
        this->m_location = static_cast<char*>(malloc(strlen(file) * strlen(sl) + 2));
        if(this->m_location != NULL)
        {
            this->m_location = strcpy(m_location,file);
            this->m_location = strcat(m_location,":");
            this->m_location = strcat(m_location,sl);
        }
    }
    else
    {
        this->m_location = NULL;
    }
}

Exception::Exception(const Exception &e)
{
    m_head = (e.m_head ? strdup(e.m_head) : NULL);
    m_message = (e.m_message ? strdup(e.m_message) : NULL);
    m_location = (e.m_location ? strdup(e.m_location) : NULL);
}

Exception& Exception::operator =(const Exception& e)
{
    if(this != &e)
    {
        if(this->m_head != NULL)
        {
            free(this->m_head);
        }

        if(this->m_message != NULL)
        {
            free(this->m_message);
        }

        if(this->m_location != NULL)
        {
            free(this->m_location);
        }

        m_head = (e.m_head ? strdup(e.m_head) : NULL);
        m_message = (e.m_message ? strdup(e.m_message) : NULL);
        m_location = (e.m_location ? strdup(e.m_location) : NULL);
    }

    return *this;
}

void Exception::GetMessage()
{
    if(this->m_head == NULL)
    {
        this->m_message = NULL;
        return;
    }
    char* p = this->m_message;
    if(p != NULL)
    {
        this->m_message = static_cast<char*>(malloc(strlen(this->m_head) + strlen(p) + 2));
    }
    else
    {
        this->m_message = static_cast<char*>(malloc(strlen(this->m_head) + 2));
    }
    if(this->m_message != NULL)
    {
        this->m_message = strcpy(this->m_message, this->m_head);
        this->m_message = strcat(this->m_message, ":");
        if(p != NULL)
        {
            this->m_message = strcat(this->m_message, p);
            free(p);
        }
    }
}

const char* Exception::Message() const
{

    return this->m_message;
}

const char* Exception::Location() const
{
    return this->m_location;
}

Exception::~Exception()
{
    if(this->m_head != NULL)
    {
        free(this->m_head);
    }

    if(this->m_message != NULL)
    {
        free(this->m_message);
    }

    if(this->m_location != NULL)
    {
        free(this->m_location);
    }
}


ArithmeticException::ArithmeticException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("ArithmeticException");
    GetMessage();
}

ArithmeticException::ArithmeticException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("ArithmeticException");
    GetMessage();
}

ArithmeticException::ArithmeticException(const ArithmeticException &e) : Exception(e)
{

}

ArithmeticException& ArithmeticException::operator =(const ArithmeticException& e)
{
    return (ArithmeticException&)(Exception::operator =(e));
}


NUllPointerException::NUllPointerException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("NUllPointerException");
    GetMessage();
}

NUllPointerException::NUllPointerException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("NUllPointerException");
    GetMessage();
}

NUllPointerException::NUllPointerException(const NUllPointerException &e) : Exception(e)
{

}

NUllPointerException& NUllPointerException::operator =(const NUllPointerException& e)
{
    return (NUllPointerException&)(Exception::operator =(e));
}


IndexOutOfBoundsException::IndexOutOfBoundsException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("IndexOutOfBoundsException");
    GetMessage();
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("IndexOutOfBoundsException");
    GetMessage();
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException &e) : Exception(e)
{

}

IndexOutOfBoundsException& IndexOutOfBoundsException::operator =(const IndexOutOfBoundsException& e)
{
    return (IndexOutOfBoundsException&)(Exception::operator =(e));
}


NoEnoughMemoryException::NoEnoughMemoryException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("NoEnoughMemoryException");
    GetMessage();
}

NoEnoughMemoryException::NoEnoughMemoryException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("NoEnoughMemoryException");
    GetMessage();
}

NoEnoughMemoryException::NoEnoughMemoryException(const NoEnoughMemoryException &e) : Exception(e)
{

}

NoEnoughMemoryException& NoEnoughMemoryException::operator =(const NoEnoughMemoryException& e)
{
    return (NoEnoughMemoryException&)(Exception::operator =(e));
}


InvalidParameterException::InvalidParameterException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("InvalidParameterException");
    GetMessage();
}

InvalidParameterException::InvalidParameterException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("InvalidParameterException");
    GetMessage();
}

InvalidParameterException::InvalidParameterException(const InvalidParameterException &e) : Exception(e)
{

}

InvalidParameterException& InvalidParameterException::operator =(const InvalidParameterException& e)
{
    return (InvalidParameterException&)(Exception::operator =(e));
}


InvalidOperationException::InvalidOperationException() : Exception(NULL, NULL, 0)
{
    this->m_head = strdup("InvalidOperationException");
    GetMessage();
}

InvalidOperationException::InvalidOperationException(const char *message, const char* file, int line) : Exception(message, file, line)
{
    this->m_head = strdup("InvalidOperationException");
    GetMessage();
}

InvalidOperationException::InvalidOperationException(const InvalidOperationException &e) : Exception(e)
{

}

InvalidOperationException& InvalidOperationException::operator =(const InvalidOperationException& e)
{
    return (InvalidOperationException&)(Exception::operator =(e));
}

}

