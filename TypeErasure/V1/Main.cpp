// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#include "Circle.h"
#include "Model.h"
#include "Shape.h"
#include "Square.h"

#include <memory>
#include <vector>

void serialize( const Circle& )
{
}

void draw( const Circle& )
{
}

void serialize( const Square& )
{
}

void draw( const Square& )
{
}

void drawAllShapes( const std::vector<Shape>& shapes )
{
   for (auto& shape : shapes)
   {
      draw(shape);
   }
}

int main()
{
   std::vector<Shape> shapes;
   shapes.emplace_back(Circle{ 2.0 });
   shapes.emplace_back(Square{ 1.5 });

   drawAllShapes(shapes);
}