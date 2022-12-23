// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#pragma once

class Square
{
public:

   explicit Square( double s ) 
      : side{ s }
   {
   }

private:

   double side;
};