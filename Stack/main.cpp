#include "lockFreeStack.h"
#include "lockFreeStackRefCounting.h"
#include "threadSafeStack.h"

int main()
{
   threadSafeStack<int> stack;
   stack.push(1);
   int value = 0;
   stack.pop(value);
   // stack.pop(value); // exception

   lockFreeStack<int> stack2;
   stack2.push(7);
   std::shared_ptr<int> oldHead = stack2.pop();

   lockFreeStackRefCounting<int> stack3;
   stack3.push(13);
   std::shared_ptr<int> previousHead = stack3.pop();

   return 0;
}