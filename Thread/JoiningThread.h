#ifndef JOINING_THREAD_H
#define JOINING_THREAD_H

#include <thread>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
class JoiningThread
{

   std::thread m_thread;

public:

   JoiningThread() noexcept = default;

   template<typename Callable, typename ... Args>
   explicit JoiningThread(Callable&& func, Args&& ... args) 
      : m_thread(std::forward<Callable>(func), std::forward<Args>(args)...)
   {
   }

   explicit JoiningThread(std::thread resourceThread) noexcept;
   JoiningThread(JoiningThread&& other) noexcept;
   JoiningThread& operator=(JoiningThread&& other) noexcept;
   JoiningThread& operator=(std::thread other) noexcept;
   ~JoiningThread() noexcept;

   void swap(JoiningThread& other) noexcept;
   
   std::thread::id get_id() const noexcept;

   bool joinable() const noexcept;
   void join();
   void detach();

   std::thread& as_thread() noexcept;
   const std::thread& as_thread() const noexcept;
};

#endif // JOINING_THREAD_H
