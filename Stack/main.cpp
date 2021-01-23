#include "threadSafeStack.h"

int main()
{
   threadSafeStack<int> stack;

   stack.push(1);
   
   int value = 0;
   
   stack.pop(value);
   stack.pop(value); // exception!
   
   return 0;
}