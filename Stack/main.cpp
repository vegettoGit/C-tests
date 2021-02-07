#include "lockFreeStack.h"
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

   return 0;
}