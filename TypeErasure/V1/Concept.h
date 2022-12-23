// Based on Klaus Iglberger's talk "Breaking Dependencies: Type Erasure - The Implementation Details"

#pragma once

#include <memory>

// External Polymorphism Design Pattern
struct ShapeConcept
{
   virtual ~ShapeConcept() = default;

   virtual void do_serialize() const = 0;
   virtual void do_draw() const = 0;

   // Prototype Design Pattern
   virtual std::unique_ptr<ShapeConcept> clone() const = 0;
};
