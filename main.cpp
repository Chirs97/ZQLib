#include <iostream>
#include <ctime>
#include "Pointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "Array.h"
#include "Stack.h"
#include "ZString.h"
#include "Sort.h"
#include "Tree.h"

using namespace std;
using namespace ZQLib;

int main()
{
    BTree<int> bt;
    BTreeNode<int>* n = NULL;

    bt.Insert(1, NULL);

    n=bt.Find(1);
    bt.Insert(2,n);
    bt.Insert(3,n);

    n=bt.Find(2);
    bt.Insert(4,n);
    bt.Insert(5,n);

    n=bt.Find(4);
    bt.Insert(8,n);
    bt.Insert(9,n);

    n=bt.Find(5);
    bt.Insert(10,n);

    n=bt.Find(3);
    bt.Insert(6,n);
    bt.Insert(7,n);

    n=bt.Find(6);
    bt.Insert(11,n, LEFT);

    BTree<int> nbt;

    nbt.Insert(0,NULL);

    n=nbt.Find(0);
    nbt.Insert(6,n);
    nbt.Insert(2,n);

    n=nbt.Find(2);
    nbt.Insert(7,n);
    nbt.Insert(8,n);

    bt.Print();

    cout << endl;

    nbt.Print();

    SharedPointer<BTree<int>> r = bt.Add(nbt);

    cout << endl;

    r->Print();

    return 0;
}
