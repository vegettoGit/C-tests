// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#pragma once

#include "Concept.h"

#include <utility>

template < typename ShapeT >
struct ShapeModel : public ShapeConcept
{
   ShapeModel( ShapeT value )
      : object{ std::move(value) }
   {
   }

   void do_serialize() const override
   {
      serialize(object);
   }

   void do_draw() const override
   {
      draw(object);
   }

   std::unique_ptr<ShapeConcept> clone() const override
   {
      return std::make_unique<ShapeModel>(*this);
   }

   ShapeT object;
};




