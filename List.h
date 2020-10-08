#ifndef LIST_H
#define LIST_H

#include "Object.h"
#include "Exception.h"

namespace ZQLib
{

/*
 * 线性表基类
 */
template<typename T>
class List : public Object
{
protected:
    List(const List&);
    List& operator=(const List&);

    int m_length;

public:
    List()
    {
        this->m_length = 0;
    }

    virtual bool Insert(int index, const T& e) = 0;
    virtual bool Remove(int index) = 0;
    virtual bool Set(int index, const T& e) = 0;
    virtual bool Get(int index, T& e) const = 0;
    virtual int Find(const T& e) const = 0;
    virtual void Clear() = 0;

    virtual bool Add(const T& e)
    {
        return Insert(this->m_length, e);
    }

    virtual int Length() const
    {
        return this->m_length;
    }

    virtual T GetBy(int index) const
    {
        T ret;

        if(!Get(index, ret))
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter index to get element ...");
        }

        return ret;
    }
};

/*
 * 顺序表
 */
template<typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;

public:
    bool Insert(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index <= this->m_length));
        ret = ret && (this->m_length < Capacity());

        if(ret)
        {
            for(int p = this->m_length - 1; p >= index; p--)
            {
                this->m_array[p + 1] = this->m_array[p];
            }

            this->m_array[index] = e;
            this->m_length++;
        }

        return ret;
    }

    bool Remove(int index)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            for(int p = index; p < this->m_length - 1; p++)
            {
                this->m_array[p] = this->m_array[p+1];
            }

            this->m_length--;
        }

        return ret;
    }

    bool Set(int index, const T &e)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            m_array[index] = e;
        }

        return ret;
    }

    bool Get(int index, T& e) const
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            e = this->m_array[index];
        }

        return ret;
    }

    int Find(const T& e) const
    {
        int ret = -1;

        for(int i = 0; i < this->m_length; i++)
        {
            if(this->m_array[i] == e)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    void Clear()
    {
        this->m_length = 0;
    }

    T& operator [](int index)
    {
        if((index >= 0) && (index < this->m_length))
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
        return (const_cast<SeqList<T>&>(*this))[index];
    }

    virtual int Capacity() const = 0;
};


/*
 * 静态顺序表
 */
template<typename T, int N>
class StaticSeqList : public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticSeqList() : List<T>()
    {
        this->m_array = this->m_space;
    }

    int Capacity() const
    {
        return N;
    }
};


/*
 * 动态顺序表
 */
template<typename T>
class DynamicSeqList : public SeqList<T>
{
protected:
    int m_capacity;

public:
    DynamicSeqList(int capacity) : List<T>()
    {
        this->m_array = new T[capacity];

        if(this->m_array != NULL)
        {
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicSeqList object ...");
        }
    }

    ~DynamicSeqList()
    {
        delete[] this->m_array;
    }

    int Capacity() const
    {
        return this->m_capacity;
    }

    void Resize(int capacity)
    {
        if(capacity != this->m_capacity)
        {
            T* array = new T[capacity];

            if(array != NULL)
            {
                int length = (this->m_length < capacity ? this->m_length : capacity);

                for(int i = 0; i < length; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicSeqList object ...");
            }
        }
    }

};


/*
 * 单链表
 */
template<typename T>
class SinglyLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    Node* Position(int index) const
    {
        Node* ret = reinterpret_cast<Node*>(&(this->m_head));

        for(int i = 0; i < index; i++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* Create()
    {
        return new Node();
    }

    virtual void Destroy(Node* pn)
    {
        delete pn;
    }

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* next;
    }m_head;

    int m_step;
    Node* m_current;

public:
    SinglyLinkList() : List<T>()
    {
        this->m_head.next = NULL;
    }

    bool Insert(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index <= this->m_length));

        if(ret)
        {
            Node* node = Create();

            if(node != NULL)
            {
                Node* current = Position(index);

                node->value = e;
                node->next = current->next;
                current->next = node;

                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to Create SinglyLinkList object ...");
            }
        }

        return ret;
    }

    bool Remove(int index)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            Node* current = Position(index);
            Node* toDel = current->next;

            if(this->m_current == toDel)
            {
                this->m_current = toDel->next;
            }

            current->next = toDel->next;

            this->m_length--;

            Destroy(toDel);
        }

        return ret;
    }

    bool Set(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            Position(index)->next->value = e;
        }

        return ret;
    }

    bool Get(int index, T& e) const
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            e = Position(index)->next->value;
        }

        return ret;
    }

    int Find(const T& e) const
    {
        int ret = -1;
        int i=0;
        Node* node = this->m_head.next;

        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }

            node = node->next;
            i++;
        }

        return ret;
    }

    void Clear()
    {
        while(this->m_head.next)
        {
            Node* toDel = this->m_head.next;

            this->m_head.next = toDel->next;

            Destroy(toDel);
        }

        this->m_length = 0;
    }

    virtual bool Move(int index, int step = 1)
    {
        bool ret = (index >= 0) && (index < this->m_length) && (step > 0);

        if(ret)
        {
            this->m_current = Position(index)->next;
            this->m_step = step;
        }

        return ret;
    }

    virtual bool End()
    {
        return (this->m_current == NULL);
    }

    virtual T& Current()
    {
        if(this->m_current != NULL)
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    virtual bool Next()
    {
        int i = 0;

        while((i < m_step) && !End())
        {
            this->m_current = this->m_current->next;
            i++;
        }

        return (i == this->m_step);
    }

    ~SinglyLinkList()
    {
        Clear();
    }

};


/*
 * 静态单链表
 */
template<typename T, int N>
class StaticSinglyLinkList : public SinglyLinkList<T>
{
protected:
    typedef typename SinglyLinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* Create()
    {
        SNode* ret = NULL;

        for(int i = 0; i < N; i++)
        {
            if(!this->m_used[i])
            {
                ret = reinterpret_cast<SNode*>(this->m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void Destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(this->m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i = 0; i < N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

public:
    StaticSinglyLinkList() : List<T>()
    {
        for(int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int Capacity()
    {
        return N;
    }

    ~StaticSinglyLinkList()
    {
        this->Clear();
    }
};


/*
 * 循环链表
 */
template<typename T>
class CircleSinglyLinkList : public SinglyLinkList<T>
{
protected:
    typedef typename SinglyLinkList<T>::Node Node;

    int mod(int i, int m) const
    {
        return (m == 0 ? 0 : i % m);
    }

    void LastToFirst() const
    {
        this->m_tail->next = this->m_head.next;
    }

    Node* m_tail;

public:
    CircleSinglyLinkList() : SinglyLinkList<T>()
    {
        this->m_tail = NULL;
    }

    bool Insert(int index, const T& e)
    {
        bool ret = true;

        index = mod(index, this->m_length + 1);

        if(index == this->m_length)
        {
            Node* node = this->Create();

            if(node != NULL)
            {
                node->value = e;
                if(this->m_tail != NULL)
                {
                    node->next = this->m_tail->next;
                    this->m_tail->next = node;
                }
                else
                {
                    node->next = NULL;
                    this->m_head.next = node;
                }
                this->m_tail = node;
                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to Create CircleSinglyLinkList object ...");
            }
        }
        else
        {
            ret = SinglyLinkList<T>::Insert(index, e);
        }

        LastToFirst();

        return ret;
    }

    bool Remove(int index)
    {
        bool ret = true;

        index = mod(index, this->m_length);

        ret = SinglyLinkList<T>::Remove(index);

        if(ret)
        {
            if(index == 0)
            {
                if(this->m_length == 0)
                {
                    this->m_head.next = NULL;
                    this->m_current = NULL;
                    this->m_tail = NULL;
                }
                else
                {
                    LastToFirst();
                }
            }
            else if(index == this->m_length)
            {
                this->m_tail = this->Position(this->m_length);
            }
        }

        return ret;
    }

    bool Set(int index, const T& e)
    {
        return SinglyLinkList<T>::Set(this->mod(index, this->m_length), e);
    }

    bool Get(int index, T& e) const
    {
        return SinglyLinkList<T>::Get(this->mod(index, this->m_length), e);
    }

    int Find(const T& e) const
    {
        int ret = -1;

        Node* slider = this->m_head.next;

        for(int i = 0; i < this->m_length; i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void Clear()
    {
        while(this->m_length > 0)
        {
            this->Remove(0);
        }
    }

    bool Move(int index, int step = 1)
    {
        return SinglyLinkList<T>::Move(mod(index, this->m_length), step);
    }

    bool End()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleSinglyLinkList()
    {
        this->Clear();
    }

};


template<typename T>
class DoublyLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* prev;
        Node* next;
    };

    Node* Position(int index) const
    {
        Node* ret = NULL;
        if(index <= this->m_length/2)
        {
            ret = reinterpret_cast<Node*>(&(this->m_head));

            for(int i = 0; i < index; i++)
            {
                ret = ret->next;
            }
        }
        else
        {
            ret = this->m_tail;

            for(int i = 0; i < this->m_length - index; i++)
            {
                ret = ret->prev;
            }
        }

        return ret;
    }

    virtual Node* Create()
    {
        return new Node();
    }

    virtual void Destroy(Node* pn)
    {
        delete pn;
    }

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* prev;
        Node* next;
    }m_head;

    Node* m_tail;
    int m_step;
    Node* m_current;

public:
    DoublyLinkList() : List<T>()
    {
        this->m_head.prev = NULL;
        this->m_head.next = NULL;
        this->m_tail = NULL;
    }

    bool Insert(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index <= this->m_length));

        if(ret)
        {
            Node* node = Create();

            if(node != NULL)
            {
                Node* current = Position(index);

                node->value = e;
                node->next = current->next;
                current->next = node;

                if(current != reinterpret_cast<Node*>(&(this->m_head)))
                {
                    node->prev = current;
                }
                else
                {
                    node->prev = NULL;
                }

                if(node->next != NULL)
                {
                    node->next->prev = node;
                }

                if(index == this->m_length)
                {
                    this->m_tail = node;
                }

                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to Create SinglyLinkList object ...");
            }
        }

        return ret;
    }

    bool Remove(int index)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            Node* current = Position(index);
            Node* toDel = current->next;

            if(this->m_current == toDel)
            {
                this->m_current = toDel->next;
            }

            current->next = toDel->next;

            if(toDel->next != NULL)
            {
                toDel->next->prev = current;
            }

            this->m_length--;

            Destroy(toDel);
        }

        return ret;
    }

    bool Set(int index, const T& e)
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            Position(index)->next->value = e;
        }

        return ret;
    }

    bool Get(int index, T& e) const
    {
        bool ret = ((index >= 0) && (index < this->m_length));

        if(ret)
        {
            e = Position(index)->next->value;
        }

        return ret;
    }

    int Find(const T& e) const
    {
        int ret = -1;
        int i=0;
        Node* node = this->m_head.next;

        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }

            node = node->next;
            i++;
        }

        return ret;
    }

    void Clear()
    {
        while(this->m_length > 0)
        {
            this->Remove(0);
        }
    }

    virtual bool Move(int index, int step = 1)
    {
        bool ret = (index >= 0) && (index < this->m_length) && (step > 0);

        if(ret)
        {
            this->m_current = Position(index)->next;
            this->m_step = step;
        }

        return ret;
    }

    virtual bool End()
    {
        return (this->m_current == NULL);
    }

    virtual T& Current()
    {
        if(this->m_current != NULL)
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    virtual bool Next()
    {
        int i = 0;

        while((i < m_step) && !End())
        {
            this->m_current = this->m_current->next;
            i++;
        }

        return (i == this->m_step);
    }

    virtual bool Prev()
    {
        int i = 0;

        while((i < m_step) && !End())
        {
            this->m_current = this->m_current->prev;
            i++;
        }

        return (i == this->m_step);
    }

    ~DoublyLinkList()
    {
        Clear();
    }
};


/*
 * 静态单链表
 */
template<typename T, int N>
class StaticDoublyLinkList : public DoublyLinkList<T>
{
protected:
    typedef typename DoublyLinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* Create()
    {
        SNode* ret = NULL;

        for(int i = 0; i < N; i++)
        {
            if(!this->m_used[i])
            {
                ret = reinterpret_cast<SNode*>(this->m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void Destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(this->m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i = 0; i < N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

public:
    StaticDoublyLinkList() : List<T>()
    {
        for(int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int Capacity()
    {
        return N;
    }

    ~StaticDoublyLinkList()
    {
        this->Clear();
    }
};


/*
 * 循环链表
 */
template<typename T>
class CircleDoublyLinkList : public DoublyLinkList<T>
{
protected:
    typedef typename DoublyLinkList<T>::Node Node;

    int mod(int i, int m) const
    {
        return (m == 0 ? 0 : i % m);
    }

    void LastToFirst() const
    {
        this->m_tail->next = this->m_head.next;
        this->m_head.next->prev = this->m_tail;
    }


public:
    CircleDoublyLinkList() : DoublyLinkList<T>()
    {

    }

    bool Insert(int index, const T& e)
    {
        bool ret = true;

        index = mod(index, this->m_length + 1);

        if(index == this->m_length)
        {
            Node* node = this->Create();

            if(node != NULL)
            {
                node->value = e;
                if(this->m_tail != NULL)
                {
                    node->next = this->m_tail->next;
                    this->m_tail->next = node;
                    node->next->prev = node;
                    node->prev = this->m_tail;
                }
                else
                {
                    node->next = NULL;
                    node->prev = NULL;
                    this->m_head.next = node;
                }
                this->m_tail = node;
                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to Create CircleSinglyLinkList object ...");
            }
        }
        else
        {
            ret = DoublyLinkList<T>::Insert(index, e);
        }

        LastToFirst();

        return ret;
    }

    bool Remove(int index)
    {
        bool ret = true;

        index = mod(index, this->m_length);

        ret = DoublyLinkList<T>::Remove(index);

        if(ret)
        {
            if(index == 0)
            {
                if(this->m_length == 0)
                {
                    this->m_head.next = NULL;
                    this->m_current = NULL;
                    this->m_tail = NULL;
                }
                else
                {
                    LastToFirst();
                }
            }
            else if(index == this->m_length)
            {
                this->m_tail = this->Position(this->m_length);
            }
        }

        return ret;
    }

    bool Set(int index, const T& e)
    {
        return DoublyLinkList<T>::Set(this->mod(index, this->m_length), e);
    }

    bool Get(int index, T& e) const
    {
        return DoublyLinkList<T>::Get(this->mod(index, this->m_length), e);
    }

    int Find(const T& e) const
    {
        int ret = -1;

        Node* slider = this->m_head.next;

        for(int i = 0; i < this->m_length; i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void Clear()
    {
        while(this->m_length > 0)
        {
            this->Remove(0);
        }
    }

    bool Move(int index, int step = 1)
    {
        return DoublyLinkList<T>::Move(mod(index, this->m_length), step);
    }

    bool End()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleDoublyLinkList()
    {
        this->Clear();
    }

};

}


#endif // LIST_H
