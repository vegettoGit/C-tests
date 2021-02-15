#ifndef LOCK_FREE_STACK_REF_COUNTING_H
#define LOCK_FREE_STACK_REF_COUNTING_H

#include <atomic>
#include <memory>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", Chapter 7, by Anthony Williams
template<typename T>
class lockFreeStackRefCounting
{

private:

   struct node;
   struct countedNodePtr
   {
      int m_externalCount;
      node* m_ptr;
   };

   struct node
   {
      std::shared_ptr<T> m_data;
      std::atomic<int> m_internalCount;
      countedNodePtr m_next;
      
      node(T const& data) 
         : m_data(std::make_shared<T>(data)),
           m_internalCount(0)
      {
      }
   };

   void increaseHeadCount(countedNodePtr& oldCounter)
   {
      countedNodePtr newCounter;
      do
      {
         newCounter = oldCounter;
         ++newCounter.m_externalCount;
      } while (!m_head.compare_exchange_strong(oldCounter, newCounter));
      oldCounter.m_externalCount = newCounter.m_externalCount;
   }

   std::atomic<countedNodePtr> m_head;
   
public:

   ~lockFreeStackRefCounting()
   {
      while (pop());
   }

   void push(T const& data)
   {
      countedNodePtr newNode;
      newNode.m_ptr = new node(data);
      newNode.m_externalCount = 1;
      newNode.m_ptr->m_next = m_head.load();
      while (!m_head.compare_exchange_weak(newNode.m_ptr->m_next, newNode));
   }

   std::shared_ptr<T> pop()
   {
      countedNodePtr oldHead = m_head.load();

      for (;;)
      {
         increaseHeadCount(oldHead);
         node* const ptr = oldHead.m_ptr;
         
         if (!ptr)
         {
            return std::shared_ptr<T>();
         }
         
         if (m_head.compare_exchange_strong(oldHead, ptr->m_next))
         {
            std::shared_ptr<T> res;
            res.swap(ptr->m_data);
            int const countIncrease = oldHead.m_externalCount - 2;
            if (ptr->m_internalCount.fetch_add(countIncrease) == -countIncrease)
            {
               delete ptr;
            }
            return res;
         }
         else if (ptr->m_internalCount.fetch_sub(1) == 1)
         {
            delete ptr;
         }
      }
   }

};

#endif // LOCK_FREE_STACK_REF_COUNTING_H
