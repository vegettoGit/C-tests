#include <iostream>
#include "ScopedThread.h"

void func(int value)
{
   std::cout << value;
}

int main()
{
   int localState;
   ScopedThread t { std::thread(func, localState) };

   return 0;
}
