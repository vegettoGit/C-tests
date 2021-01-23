#ifndef THREAD_SAFE_STACK_H
#define THREAD_SAFE_STACK_H

#include <exception>
#include <mutex>
#include <stack>

struct emptyStack : std::exception
{
   const char* what() const throw();
};

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", Chapter 6, by Anthony Williams
template<typename T>
class threadSafeStack
{

private:

   std::stack<T> m_data;
   mutable std::mutex m_mutex;

public:
   
   threadSafeStack() = default;
   
   threadSafeStack(const threadSafeStack& other)
   {
      std::lock_guard<std::mutex> lock(other.m);
      m_data = other.m_data;
   }
   
   threadSafeStack& operator=(const threadSafeStack&) = delete;
   
   void push(T newValue)
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_data.push(std::move(newValue));
   }

   std::shared_ptr<T> pop()
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      if (m_data.empty())
      {
         throw emptyStack();
      }
      
      std::shared_ptr<T> const result(std::make_shared<T>(std::move(m_data.top())));
      m_data.pop();
      return result;
   }

   void pop(T& value)
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      if (m_data.empty())
      {
         throw emptyStack();
      }

      value = std::move(m_data.top());
      m_data.pop();
   }

   bool empty() const
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_data.empty();
   }

};

#endif // THREAD_SAFE_STACK_H
