#ifndef TREE_H
#define TREE_H

#include "Object.h"
#include "Pointer.h"
#include "List.h"
#include "Queue.h"
#include "Array.h"
#include <iostream>

using namespace std;

namespace ZQLib
{

template<typename T>
class TreeNode : public Object
{
protected:
    TreeNode(TreeNode<T>&);
    TreeNode<T>& operator =(const TreeNode<T>&);

    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

    bool m_flag;

public:
    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool Flag()
    {
        return this->m_flag;
    }

    virtual ~TreeNode() = 0;

    T value;
    TreeNode<T>* parent;
};

template<typename T>
TreeNode<T>::~TreeNode()
{

}

template<typename T>
class Tree : public Object
{
protected:
    Tree(const Tree<T>&);
    Tree<T>& operator =(const Tree<T>&);

    TreeNode<T>* m_root;

public:
    Tree()
    {
        m_root = NULL;
    }

    virtual bool Insert(TreeNode<T>* node) = 0;
    virtual bool Insert(const T& value, TreeNode<T>* parent) = 0;
    virtual SharedPointer<Tree<T>> Remove(const T& value) = 0;
    virtual SharedPointer<Tree<T>> Remove(TreeNode<T>* node) = 0;
    virtual TreeNode<T>* Find(const T& value) const = 0;
    virtual TreeNode<T>* Find(TreeNode<T>* node) const = 0;
    virtual TreeNode<T>* Root() const = 0;
    virtual int Degree() const = 0;
    virtual int Count() const = 0;
    virtual int Height() const = 0;
    virtual void Clear() = 0;
    virtual bool Begin() = 0;
    virtual bool End() = 0;
    virtual bool Next() = 0;
    virtual T Current() = 0;

};

template<typename T>
class GTreeNode : public TreeNode<T>
{
public:
    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    SinglyLinkList<GTreeNode<T>*> child;
};

template<typename T>
class GTree : public Tree<T>
{
protected:
    GTreeNode<T>* Find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.Move(0); !node->child.End() && (ret == NULL); node->child.Next())
                {
                    ret = Find(node->child.Current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* Find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {
                for(node->child.Move(0); !node->child.End() && (ret == NULL); node->child.Next())
                {
                    ret = Find(node->child.Current(), obj);
                }
            }
        }

        return ret;
    }

    void Free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.Move(0); !node->child.End(); node->child.Next())
            {
                Free(node->child.Current());
            }
            if(node->Flag())
            {
                delete node;
            }
        }
    }

    void Remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if(ret != NULL)
        {
            if(this->Root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                SinglyLinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                child.Remove(child.Find(node));

                node->parent = NULL;
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
    }

    int Count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            for(node->child.Move(0); !node->child.End(); node->child.Next())
            {
                ret += Count(node->child.Current());
            }
        }

        return ret;
    }

    int Height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            for(node->child.Move(0); !node->child.End(); node->child.Next())
            {
                int h = Height(node->child.Current());

                if(ret < h)
                {
                    ret = h;
                }
            }

            ret++;
        }

        return ret;
    }

    int Degree(GTreeNode<T>* node) const
    {
        int ret = this->Root()->child.Length();

        if(node != NULL)
        {
            for(node->child.Move(0); !node->child.End(); node->child.Next())
            {
                int d = Degree(node->child.Current());

                if(ret < d)
                {
                    ret = d;
                }
            }
        }

        return ret;

    }

    void Print(GTreeNode<T>* node, int layer) const
    {
        if(node != NULL)
        {
            cout << node->value << "\t";

            for(node->child.Move(0); !node->child.End();)
            {
                cout << "--";
                Print(node->child.Current(), layer+1);
                node->child.Next();
                if(!node->child.End())
                {
                    cout << endl;
                    for(int i=0;i<layer;i++)
                    {
                        cout << "|" << "\t" << "  ";
                    }

                    if(!node->child.End())
                    {
                        cout << "|" << "\t";
                    }
                }
                else
                {
                    cout << endl;
                    for(int i=0;i<layer;i++)
                    {
                        cout << "|" << "\t" << "  ";
                    }
                }
            }

        }
    }

    LinkQueue<GTreeNode<T>*> m_queue;

public:
    bool Insert(TreeNode<T>* node)
    {
        bool ret = true;

        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = Find(node->parent);

                if(np != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    if(np->child.Find(n) < 0)
                    {
                        np->child.Add(n);
                    }
                }
                else
                {
                    ret = false;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool Insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = GTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;

            ret = this->Insert(node);

            if(!ret)
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> Remove(const T& value)
    {
        GTree<T>* ret = NULL;

        GTreeNode<T>* node = this->Find(value);

        if(node != NULL)
        {
            Remove(node, ret);
            m_queue.Clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Cannot find the node via parameter value ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> Remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = this->Find(node);

        if(node != NULL)
        {
            Remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.Clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    GTreeNode<T>* Find(const T& value) const
    {
        return Find(Root(), value);
    }

    GTreeNode<T>* Find(TreeNode<T>* node) const
    {
        return Find(Root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* Root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int Degree() const
    {
        return Degree(dynamic_cast<GTreeNode<T>*>(this->m_root));
    }

    int Count() const
    {
        return Count(dynamic_cast<GTreeNode<T>*>(this->m_root));
    }

    int Height() const
    {
        return Height(dynamic_cast<GTreeNode<T>*>(this->m_root));
    }

    void Clear()
    {
        Free(this->Root());
        this->m_root = NULL;
        m_queue.Clear();
    }

    bool Begin()
    {
        bool ret = (this->Root() != NULL);

        if(ret)
        {
            m_queue.Clear();
            m_queue.Add(this->Root());
        }

        return ret;
    }

    bool End()
    {
        return (m_queue.Length() == 0);
    }

    bool Next()
    {
        bool ret = (m_queue.Length() > 0);

        if(ret)
        {
            GTreeNode<T>* node = m_queue.Front();
            m_queue.Remove();
            for(node->child.Move(0); !node->child.End(); node->child.Next())
            {
                m_queue.Add(node->child.Current());
            }
        }

        return ret;
    }

    T Current()
    {
        if(!End())
        {
            return m_queue.Front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    void Print() const
    {
        Print(dynamic_cast<GTreeNode<T>*>(this->m_root), 0);
    }

    ~GTree()
    {
        Clear();
    }
};

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template<typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    BTreeNode<T>* left;
    BTreeNode<T>* right;
};

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder
};

template<typename T>
class BTree : public Tree<T>
{
protected:
    BTreeNode<T>* Find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = Find(node->left, value);
                }

                if(ret == NULL)
                {
                    ret = Find(node->right, value);
                }
            }
        }

        return ret;
    }

    BTreeNode<T>* Find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node == obj)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = Find(node->left, obj);
                }

                if(ret == NULL)
                {
                    ret = Find(node->right, obj);
                }
            }
        }

        return ret;
    }

    bool Insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        if(pos == ANY)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == LEFT)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == RIGHT)
        {
            if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    void Remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree();

        if(ret != NULL)
        {
            if(this->Root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if(parent->left == node)
                {
                    parent->left = NULL;
                }
                else if(parent->right == node)
                {
                    parent->right = NULL;
                }

                node->parent = NULL;
            }
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
    }

    void Free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            Free(node->left);
            Free(node->right);

            if(node->Flag())
            {
                delete node;
            }
        }
    }

    int Count(BTreeNode<T>* node) const
    {
        return (node ? (Count(node->left) + Count(node->right) + 1) : 0);
    }

    int Height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {

            int hl = Height(node->left);
            int hr = Height(node->right);

            ret = hl > hr ? hl : hr;

            ret++;
        }

        return ret;
    }

    int Degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            BTreeNode<T>* child[] = {node->left, node->right};

            ret = !!node->left + !!node->right;

            for(int i = 0; (i < 2) && (ret < 2); i++)
            {
                int d = Degree(child[i]);

                if(ret < d)
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

    void Print(BTreeNode<T>* node, int layer) const
    {
        if(node != NULL)
        {
            cout << node->value << "\t";
            if(node->left != NULL)
            {
                cout << "--";
                Print(node->left, layer + 1);

            }
            if(node->right != NULL)
            {
                cout << endl;
                for(int i=0;i<layer;i++)
                {
                    cout << "|" << "\t" << "  ";
                }
                cout << "|" << "\t" << "--";
                Print(node->right, layer + 1);
                cout << endl;
                for(int i=0;i<layer;i++)
                {
                    cout << "|" << "\t" << "  ";
                }
            }
        }
    }

    void PreOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            queue.Add(node);
            PreOrderTraversal(node->left, queue);
            PreOrderTraversal(node->right,queue);
        }
    }

    void InOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            InOrderTraversal(node->left, queue);
            queue.Add(node);
            InOrderTraversal(node->right,queue);
        }
    }

    void PostOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            PostOrderTraversal(node->left, queue);
            PostOrderTraversal(node->right,queue);
            queue.Add(node);
        }
    }

    BTreeNode<T>* Clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            ret = BTreeNode<T>::NewNode();

            if(ret != NULL)
            {
                ret->value = node->value;

                ret->left = Clone(node->left);
                ret->right = Clone(node->right);

                if(ret->left != NULL)
                {
                    ret->left->parent = ret;
                }

                if(ret->right != NULL)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    bool Equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if(lh == rh)
        {
            return true;
        }
        else if((lh != NULL) && (rh != NULL))
        {
            return (lh->value == rh->value) && Equal(lh->left, rh->left) && Equal(lh->right, rh->right);
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* Add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = NULL;

        if(lh == NULL && rh != NULL)
        {
            ret = Clone(rh);
        }
        else if(lh != NULL && rh == NULL)
        {
            ret = Clone(lh);
        }
        else if(lh != NULL && rh != NULL)
        {
            ret = BTreeNode<T>::NewNode();

            if(ret != NULL)
            {
                ret->value = lh->value + rh->value;

                ret->left = Add(lh->left, rh->left);
                ret->right = Add(lh->right, rh->right);

                if(ret->left != NULL)
                {
                    ret->left->parent = ret;
                }

                if(ret->right != NULL)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    LinkQueue<BTreeNode<T>*> m_queue;

public:
    bool Insert(TreeNode<T>* node)
    {
        return this->Insert(node, ANY);
    }

    bool Insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = this->Find(node->parent);

                if(np != NULL)
                {
                    ret = this->Insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool Insert(const T& value, TreeNode<T>* parent)
    {
        return this->Insert(value, parent, ANY);
    }

    bool Insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->parent = parent;
            node->value = value;
            ret = this->Insert(node, pos);

            if(!ret)
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> Remove(const T& value)
    {
        BTree<T>* ret = NULL;

        BTreeNode<T>* node = this->Find(value);

        if(node != NULL)
        {
            this->Remove(node, ret);
            this->m_queue.Clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> Remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        node = this->Find(node);

        if(node != NULL)
        {
            this->Remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            this->m_queue.Clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    BTreeNode<T>* Find(const T& value) const
    {
        return Find(this->Root(), value);
    }

    BTreeNode<T>* Find(TreeNode<T>* node) const
    {
        return Find(this->Root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* Root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int Degree() const
    {
        return this->Degree(this->Root());
    }

    int Count() const
    {
        return this->Count(this->Root());
    }

    int Height() const
    {
        return this->Height(this->Root());
    }

    void Clear()
    {
        this->Free(this->Root());
        this->m_root = NULL;
        this->m_queue.Clear();
    }

    bool Begin()
    {
        bool ret = (this->Root() != NULL);

        if(ret)
        {
            m_queue.Clear();
            m_queue.Add(this->Root());
        }

        return ret;
    }

    bool End()
    {
        return (m_queue.Length() == 0);
    }

    bool Next()
    {
        bool ret = (m_queue.Length() > 0);

        if(ret)
        {
            BTreeNode<T>* node = m_queue.Front();
            m_queue.Remove();
            if(node->left != NULL)
            {
                m_queue.Add(node->left);
            }
            if(node->right != NULL)
            {
                m_queue.Add(node->right);
            }
        }

        return ret;
    }

    T Current()
    {
        if(!End())
        {
            return m_queue.Front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer<Array<T>> Traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        switch (order)
        {
        case PreOrder:
            PreOrderTraversal(this->Root(), queue);
            break;
        case InOrder:
            InOrderTraversal(this->Root(), queue);
            break;
        case PostOrder:
            PostOrderTraversal(this->Root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }

        ret = new DynamicArray<T>(queue.Length());

        if(ret != NULL)
        {
            for(int i = 0; i < ret->Length(); i++, queue.Remove())
            {
                ret->Set(i, queue.Front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return array ...");
        }

        return ret;
    }

    SharedPointer<BTree<T>> Clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != NULL)
        {
            ret->m_root = Clone(this->Root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }

        return ret;
    }

    SharedPointer<BTree<T>> Add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != NULL)
        {
            ret->m_root = this->Add(this->Root(), btree.Root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }

        return ret;
    }

    bool operator ==(const BTree<T>& btree)
    {
        return this->Equal(this->Root(), btree.Root());
    }

    bool operator !=(const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    void Print() const
    {
        Print(dynamic_cast<BTreeNode<T>*>(this->m_root), 0);
    }

    ~BTree()
    {
        this->Clear();
    }
};

}

#endif // TREE_H
