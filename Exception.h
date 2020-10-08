#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace ZQLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_head;
    char* m_message;
    char* m_location;

    Exception();
    Exception(const char *message, const char* file, int line);
    Exception(const Exception& e);

    void GetMessage();

public:
    Exception& operator =(const Exception& e);

    virtual const char* Message() const;
    virtual const char* Location() const;

    virtual ~Exception() = 0;

private:

};

class ArithmeticException : public Exception
{
public:
    ArithmeticException();
    ArithmeticException(const char *message, const char* file, int line);
    ArithmeticException(const ArithmeticException& e);

    ArithmeticException& operator =(const ArithmeticException& e);
};

class NUllPointerException : public Exception
{
public:
    NUllPointerException();
    NUllPointerException(const char *message, const char* file, int line);
    NUllPointerException(const NUllPointerException& e);

    NUllPointerException& operator =(const NUllPointerException& e);
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException();
    IndexOutOfBoundsException(const char *message, const char* file, int line);
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e);

    IndexOutOfBoundsException& operator =(const IndexOutOfBoundsException& e);
};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException();
    NoEnoughMemoryException(const char *message, const char* file, int line);
    NoEnoughMemoryException(const NoEnoughMemoryException& e);

    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& e);
};

class InvalidParameterException : public Exception
{
public:
    InvalidParameterException();
    InvalidParameterException(const char *message, const char* file, int line);
    InvalidParameterException(const InvalidParameterException& e);

    InvalidParameterException& operator =(const InvalidParameterException& e);
};

class InvalidOperationException : public Exception
{
public:
    InvalidOperationException();
    InvalidOperationException(const char *message, const char* file, int line);
    InvalidOperationException(const InvalidOperationException& e);

    InvalidOperationException& operator =(const InvalidOperationException& e);
};

}

#endif // EXCEPTION_H
