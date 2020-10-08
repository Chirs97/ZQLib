#ifndef STACK_H
#define STACK_H

#include "Object.h"
#include "Exception.h"
#include "List.h"

using namespace ZQLib;

namespace ZQLib
{

template<typename T>
class Stack : public Object
{

public:
    virtual void Push(const T& e) = 0;
    virtual void Pop() = 0;
    virtual T Top() const = 0;
    virtual void Clear() = 0;
    virtual int Size() const = 0;
};


template<typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()
    {
        this->m_top = -1;
        this->m_size = 0;
    }

    int Capacity() const
    {
        return N;
    }

    void Push(const T& e)
    {
        if(this->m_size < N)
        {
            this->m_space[this->m_top + 1] = e;
            this->m_top++;
            this->m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void Pop()
    {
        if(this->m_size > 0)
        {
            this->m_top--;
            this->m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T Top() const
    {
        if(this->m_size > 0)
        {
            return this->m_space[this->m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void Clear()
    {
        this->m_top = -1;
        this->m_size = 0;
    }

    int Size() const
    {
        return this->m_size;
    }

};


template<typename T>
class LinkStack : public Stack<T>
{
protected:
    SinglyLinkList<T> m_sl;

public:
    void Push(const T& e)
    {
        this->m_sl.Insert(0, e);
    }

    void Pop()
    {
        if(this->m_sl.Length() > 0)
        {
            this->m_sl.Remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T Top() const
    {
        if(this->m_sl.Length() > 0)
        {
            return this->m_sl.GetBy(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void Clear()
    {
        this->m_sl.Clear();
    }

    int Size() const
    {
        return this->m_sl.Length();
    }

};

}



#endif // STACK_H
