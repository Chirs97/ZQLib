#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace ZQLib
{

template<typename T>
class Array : public Object
{
protected:
    T* m_array;

public:
    virtual int Length() const = 0;
    virtual bool Set(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index < this->Length()));

        if(ret)
        {
            this->m_array[index] = e;
        }

        return ret;
    }

    virtual bool Get(int index, T& e)
    {
        bool ret = ((index >= 0) && (index < this->Length()));

        if(ret)
        {
            e = this->m_array[index];
        }

        return ret;
    }

    T& operator [](int index)
    {
        if((index >= 0) && (index < this->Length()))
        {
            return this->m_array[index];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }
    }

    T operator [](int index) const
    {
        return (const_cast<Array<T>&>(*this))[index];
    }

};


template<typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];

public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    StaticArray(const StaticArray<T,N>& obj)
    {
        this->m_array = m_space;

        for(int i = 0; i < N; i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj)
    {
        if(this != &obj)
        {
            for(int i = 0; i < N; i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }


    int Length() const
    {
        return N;
    }

};


template<typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* Copy(T* array, int length, int newLength)
    {
        T* ret = new T[newLength];

        if(ret != NULL)
        {
            int size = (length < newLength) ? length : newLength;

            for(int i = 0; i < size; i++)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void Update(T* array, int length)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicList object ...");
        }
    }

    void Init(T* array, int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        Init(new T[length], length);
    }

    DynamicArray(const DynamicArray& obj)
    {
        Init(Copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        Update(obj.m_array, obj.m_length);
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            Update(Copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    int Length() const
    {
        return m_length;
    }

    void Resize(int length)
    {
        if(this->m_length != length)
        {
            Update(Copy(this->m_array, this->m_length, length), length);
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}


#endif // ARRAY_H
