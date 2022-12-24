// Based on Sy Brand's talk "Dynamic Polymorphism with Metaclasses and Code Injection"

#pragma once

#include "VTable.h"

#include <utility>

struct animal
{
   void* concrete_;
   vtable const* vtable_;

   template <class T>
   animal(T const& t) :
      concrete_(new T(t)),
      vtable_(&vtable_for<T>)
   {
   }

   animal(animal const& rhs) :
      concrete_(rhs.vtable_->clone_(rhs.concrete_)),
      vtable_(rhs.vtable_)
   {
   }

   animal(animal&& rhs) :
      concrete_(rhs.vtable_->move_clone_(rhs.concrete_)),
      vtable_(rhs.vtable_)
   {
   }

   animal& operator=(animal const& rhs)
   {
      vtable_->destroy_(concrete_);

      concrete_ = rhs.vtable_->clone_(rhs.concrete_);
      vtable_ = rhs.vtable_;
      
      return *this;
   }

   animal& operator=(animal&& rhs)
   {
      vtable_->destroy_(concrete_);

      concrete_ = rhs.vtable_->move_clone_(rhs.concrete_);
      vtable_ = rhs.vtable_;

      return *this;
   }

   void speak()
   {
      vtable_->speak(concrete_);
   }

   ~animal()
   {
      vtable_->destroy_(concrete_);
   }
};
