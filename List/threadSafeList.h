#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <mutex>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
template<typename T>
class threadSafeList
{
   struct node
   {
      std::mutex mutex;
      std::shared_ptr<T> data;
      std::unique_ptr<node> next;

      node() = default;

      node(T const& value) 
         : data(std::make_shared<T>(value))
      {
      }
   };

   node head;

public:
   
   threadSafeList() = default;
   
   ~threadSafeList()
   {
      removeIf([](node const&) 
         {
            return true;
         });
   }

   threadSafeList(threadSafeList const& other) = delete;
   threadSafeList& operator=(threadSafeList const& other) = delete;

   void pushFront(T const& value)
   {
      std::unique_ptr<node> newNode(new node(value));
      std::lock_guard<std::mutex> lock(head.mutex);
      newNode->next = std::move(head.next);
      head.next = std::move(newNode);
   }

   template<typename Function>
   void forEach(Function f)
   {
      node* current = &head;
      std::unique_lock<std::mutex> lock(head.mutex);
      
      while (node* const next = current->next.get())
      {
         std::unique_lock<std::mutex> nextLock(next->mutex);
         lock.unlock();
         f(*next->data);
         current = next;
         lock = std::move(nextLock);
      }
   }

   template<typename Predicate>
   std::shared_ptr<T> findFirstIf(Predicate p)
   {
      node* current = &head;
      std::unique_lock<std::mutex> lock(head.mutex);
      
      while (node* const next = current->next.get())
      {
         std::unique_lock<std::mutex> nextLock(next->mutex);
         lock.unlock();
         if (p(*next->data))
         {
            return next->data;
         }
         current = next;
         lock = std::move(nextLock);
      }
      return std::shared_ptr<T>();
   }

   template<typename Predicate>
   void removeIf(Predicate p)
   {
      node* current = &head;
      std::unique_lock<std::mutex> lock(head.mutex);
      
      while (node* const next = current->next.get())
      {
         std::unique_lock<std::mutex> nextLock(next->mutex);
         if (p(*next->data))
         {
            std::unique_ptr<node> oldNext = std::move(current->next);
            current->next = std::move(next->next);
            nextLock.unlock();
         }
         else
         {
            lock.unlock();
            current = next;
            lock = std::move(nextLock);
         }
      }
   }
};

#endif // THREAD_SAFE_LIST_H
