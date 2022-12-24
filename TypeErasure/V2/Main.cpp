// Based on Sy Brand's talk "Dynamic Polymorphism with Metaclasses and Code Injection"

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"


#include <vector>

int main()
{
   animal c = cat{};
   c.speak();

   animal d = dog{};
   d.speak();

   animal a = cat{};
   a.speak();
   a = dog{};
   a.speak();

   animal b = a;

   std::vector<animal> animals{ cat{}, dog{} };

   for (auto&& a : animals)
   {
      a.speak();
   }

   return 0;
}