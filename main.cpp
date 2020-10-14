#include <iostream>
#include <ctime>
#include "Pointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "Array.h"
#include "Stack.h"
#include "ZString.h"
#include <cstring>

using namespace std;
using namespace ZQLib;



int main()
{
    ZString s = "ababax";
    ZString s1 = s.SubString(3, 2);

    cout << s1.ToCharArray() <<endl;

    return 0;
}
