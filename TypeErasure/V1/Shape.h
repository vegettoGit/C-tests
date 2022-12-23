// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#pragma once

#include "Model.h"

#include <memory>

class Shape
{
   friend void serialize( const Shape& shape )
   {
      shape.pimpl->do_serialize();
   }

   friend void draw( const Shape& shape )
   {
      shape.pimpl->do_draw();
   }

   // Bridge Design Pattern
   std::unique_ptr<ShapeConcept> pimpl;

public:

   template < typename ShapeT > 
   Shape( const ShapeT& s )
      : pimpl{ std::make_unique< ShapeModel< ShapeT> >( s ) }
   {
   }

   Shape( const Shape& other )
      : pimpl(other.pimpl->clone())
   {
   }

   Shape& operator=( const Shape& other )
   {
      Shape tmp(other);
      std::swap(pimpl, tmp.pimpl);
      return *this;
   }
   
   Shape(Shape&&) = default;
   Shape& operator=(Shape&&) = default;
};
