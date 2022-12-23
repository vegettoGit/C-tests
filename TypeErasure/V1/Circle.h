// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#pragma once

class Circle
{
public:

   explicit Circle( double rad )
      : radius{ rad }
   {
   }

private:

   double radius;
};