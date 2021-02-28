#include <iostream>

#include "JoiningThread.h"
#include "ScopedThread.h"

void func(int value)
{
   std::cout << value << std::endl;
}

int main()
{
   int localState  = 7;
   int localState2 = 20;
   ScopedThread  t { std::thread(func, localState) };
   JoiningThread t2{ std::thread(func, localState2) };

   return 0;
}
