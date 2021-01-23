#include "threadSafeStack.h"

const char* emptyStack::what() const throw()
{
   return "cannot pop from an empty stack";
};
