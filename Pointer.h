#ifndef POINTER_H
#define POINTER_H

#include <cstdlib>
#include "Object.h"
#include "Exception.h"

namespace ZQLib
{

template<typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* p = NULL)
    {
        this->m_pointer = p;
    }

    T* operator ->()
    {
        return this->m_pointer;
    }

    const T* operator ->() const
    {
        return this->m_pointer;
    }

    T& operator *()
    {
        return *(this->m_pointer);
    }

    const T& operator *() const
    {
        return *(this->m_pointer);
    }

    bool IsNull() const
    {
        return (this->m_pointer == NULL);
    }

    T* Get() const
    {
        return this->m_pointer;
    }
};


template<typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {

    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator =(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* temp = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete temp;
        }

        return *this;
    }

    ~SmartPointer()
    {
        if(this->m_pointer != NULL)
        {
            delete this->m_pointer;
        }
    }
};


template<typename T>
class SharedPointer : public Pointer<T>
{
protected:
    void Assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if(this->m_ref)
        {
            (*(this->m_ref))++;
        }
    }

    int* m_ref;

public:
    SharedPointer(T* p = NULL) : Pointer<T>(p), m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

            if(this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        Assign(obj);
    }

    SharedPointer<T>& operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            Clear();
            Assign(obj);
        }

        return *this;
    }

    void Clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if(ref)
        {
            (*(ref))--;

            if(*ref == 0)
            {
                std::free(ref);
                delete toDel;
            }
        }


    }

    ~SharedPointer()
    {
        Clear();
    }
};

template<typename T>
bool operator ==(const Pointer<T>& l, const Pointer<T>& r)
{
    return (l.Get() == r.Get());
}

}

#endif // POINTER_H
