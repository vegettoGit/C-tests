#ifndef LOCK_FREE_STACK_H
#define LOCK_FREE_STACK_H

#include <atomic>
#include <memory>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", Chapter 7, by Anthony Williams
template<typename T>
class lockFreeStack
{

private:
   
   struct node
   {
      std::shared_ptr<T> m_data;
      node* m_next;
      node(T const& data)
         : m_data(std::make_shared<T>(data)),
           m_next(nullptr)
      {
      }
   };

   std::atomic<node*> m_head = nullptr;
   std::atomic<node*> m_toBeDeleted = nullptr;
   std::atomic<unsigned> m_threadsInPop = 0;

   static void deleteNodes(node* nodes)
   {
      while (nodes)
      {
         node* next = nodes->m_next;
         delete nodes;
         nodes = next;
      }
   }

   void tryReclaim(node* oldHead)
   {
      if (m_threadsInPop == 1)
      {
         node* nodesToDelete = m_toBeDeleted.exchange(nullptr);
         if (!--m_threadsInPop)
         {
            deleteNodes(nodesToDelete);
         }
         else if (nodesToDelete)
         {
            chainPendingNodes(nodesToDelete);
         }
         delete oldHead;
      }
      else
      {
         chainPendingNode(oldHead);
         --m_threadsInPop;
      }
   }

   void chainPendingNodes(node* nodes)
   {
      node* last = nodes;
      while (node* const next = last->m_next)
      {
         last = next;
      }
      chainPendingNodes(nodes, last);
   }

   void chainPendingNodes(node* first, node* last)
   {
      last->m_next = m_toBeDeleted;
      while (!m_toBeDeleted.compare_exchange_weak(last->m_next, first));
   }

   void chainPendingNode(node* n)
   {
      chainPendingNodes(n, n);
   }

public:

   void push(T const& data)
   {
      node* const newNode = new node(data);
      newNode->m_next = m_head.load();
      while (!m_head.compare_exchange_weak(newNode->m_next, newNode));
   }

   std::shared_ptr<T> pop()
   {
      ++m_threadsInPop;
      node* oldHead = m_head.load();
      while (oldHead && !m_head.compare_exchange_weak(oldHead, oldHead->m_next));
      std::shared_ptr<T> res;
      if (oldHead)
      {
         res.swap(oldHead->m_data);
      }
      tryReclaim(oldHead);
      return res;
   }

};

#endif // LOCK_FREE_STACK_H
