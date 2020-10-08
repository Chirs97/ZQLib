#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"
#include "Exception.h"
#include "List.h"

using namespace ZQLib;

namespace ZQLib
{

template<typename T>
class Queue : public Object
{
public:
    virtual void Add(const T& e) = 0;
    virtual void Remove() = 0;
    virtual T Front() const = 0;
    virtual void Clear() = 0;
    virtual int Length() const = 0;
};


template<typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;

public:
    StaticQueue()
    {
        this->m_front = 0;
        this->m_rear = 0;
        this->m_length = 0;
    }

    int Capacity() const
    {
        return N;
    }

    void Add(const T& e)
    {
        if(this->m_length < N)
        {
            this->m_space[this->m_rear] = e;
            this->m_rear = (this->m_rear + 1) % N;
            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
        }
    }

    void Remove()
    {
        if(this->m_length > 0)
        {
            this->m_front = (this->m_front + 1) % N;
            this->m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T Front() const
    {
        if(this->m_length > 0)
        {
            return this->m_space[this->m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void Clear()
    {
        this->m_front = 0;
        this->m_rear = 0;
        this->m_length = 0;
    }

    int Length() const
    {
        return this->m_length;
    }
};


template<typename T>
class LinkQueue : public Queue<T>
{
protected:
    CircleSinglyLinkList<T> m_sl;

public:
    void Add(const T& e)
    {
        this->m_sl.Add(e);
    }

    void Remove()
    {
        if(this->m_sl.Length() > 0)
        {
            this->m_sl.Remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T Front() const
    {
        if(this->m_sl.Length() > 0)
        {
            return this->m_sl.GetBy(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void Clear()
    {
        this->m_sl.Clear();
    }

    int Length() const
    {
        return this->m_sl.Length();
    }
};
}


#endif // QUEUE_H
