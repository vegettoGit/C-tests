#include "threadSafeList.h"
#include <iostream>

int main()
{
   threadSafeList<int> list;

   list.pushFront(1);
   list.pushFront(2);

   list.forEach([](int& value)
      {
         value *= 2;
      });

   list.forEach([](int& value)
      {
         std::cout << value << " ";
      });

   std::shared_ptr<int> valuePtr = list.findFirstIf([](int& value)
      {
         return value > 3;
      });

   if (valuePtr)
   {
      std::cout << "\nFound value " << *valuePtr;
   }

   list.removeIf([](int& value)
      {
         return value > 3;
      });

   list.forEach([](int& value)
      {
         std::cout << "\n" << value;
      });

   return 0;
}
