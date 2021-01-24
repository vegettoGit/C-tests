#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <condition_variable>
#include <queue>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", Chapter 6, by Anthony Williams
template<typename T>
class threadSafeQueue
{

private:

   mutable std::mutex m_mutex;
   std::queue<std::shared_ptr<T>> m_data;
   std::condition_variable m_dataCondition;

public:

   threadSafeQueue() = default;

   void waitAndPop(T& value)
   {
      std::unique_lock<std::mutex> lock(m_mutex);
      
      m_dataCondition.wait(lock, [this]
         {
            return !m_data.empty();
         });

      value = std::move(*m_data.front());
      m_data.pop();
   }

   std::shared_ptr<T> waitAndPop()
   {
      std::unique_lock<std::mutex> lock(m_mutex);

      m_dataCondition.wait(lock, [this]
         {
            return !m_data.empty();
         });

      std::shared_ptr<T> res = m_data.front();
      m_data.pop();
      return res;
   }

   bool tryPop(T& value)
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      
      if (m_data.empty())
      {
         return false;
      }
      
      value = std::move(*m_data.front());
      m_data.pop();
      return true;
   }

   std::shared_ptr<T> tryPop()
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      
      if (m_data.empty())
      {
         return std::shared_ptr<T>();
      }
      
      std::shared_ptr<T> res = m_data.front();
      m_data.pop();
      return res;
   }

   void push(T newValue)
   {
      std::shared_ptr<T> data(std::make_shared<T>(std::move(newValue)));
      std::lock_guard<std::mutex> lock(m_mutex);
      m_data.push(data);
      m_dataCondition.notify_one();
   }

   bool empty() const
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_data.empty();
   }

};

#endif // THREAD_SAFE_QUEUE_H
