// Based on Sy Brand's talk "Dynamic Polymorphism with Metaclasses and Code Injection"

#pragma once

#include <utility>

struct vtable
{
   void (*speak) (void* ptr);
   void (*destroy_) (void* ptr);
   void* (*clone_) (void* ptr);
   void* (*move_clone_) (void* ptr);
};

template <class Concrete>
constexpr vtable vtable_for
{
   // function which calls speak
   [](void* ptr) { static_cast<Concrete*>(ptr)->speak(); },
   // function which deletes object
   [](void* ptr) { delete static_cast<Concrete*>(ptr); },
   [](void* ptr) -> void* { return new Concrete(*static_cast<Concrete*>(ptr)); },
   [](void* ptr) -> void* { return new Concrete(std::move(*static_cast<Concrete*>(ptr))); }
};
