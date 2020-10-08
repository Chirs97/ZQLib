#include <iostream>
#include <ctime>
#include "Pointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "Array.h"
#include "Stack.h"

using namespace std;
using namespace ZQLib;

class Base
{
public:
    void Print()
    {
        cout << "this is Base" << endl;
    }
};

class A : public Base
{
public:
    A() {}

    void Print()
    {
        cout << "this is A" << endl;
    }
};


int main()
{
    Base* p = new A;

    p->Print();


    return 0;
}
