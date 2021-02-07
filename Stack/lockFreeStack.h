#ifndef LOCK_FREE_STACK_H
#define LOCK_FREE_STACK_H

#include <atomic>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", Chapter 7, by Anthony Williams
template<typename T>
class lockFreeStack
{

private:
   
   struct node
   {
      T m_data;
      node* m_next;
      node(T const& data)
         : m_data(data),
           m_next(nullptr)
      {
      }
   };

   std::atomic<node*> m_head = nullptr;

public:

   void push(T const& data)
   {
      node* const newNode = new node(data);
      newNode->m_next = m_head.load();
      while (!m_head.compare_exchange_weak(newNode->m_next, newNode));
   }

};

#endif // LOCK_FREE_STACK_H
