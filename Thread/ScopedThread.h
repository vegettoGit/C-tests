#ifndef SCOPED_THREAD_H
#define SCOPED_THREAD_H

#include <stdexcept>
#include <thread>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
class ScopedThread
{
   std::thread m_resourceThread;

public:

   explicit ScopedThread(std::thread resourceThread) 
      :  m_resourceThread(std::move(resourceThread))
   {
      if (!resourceThread.joinable())
      {
         throw std::logic_error("No thread");
      }
   }
   ~ScopedThread()
   {
      m_resourceThread.join();
   }

   ScopedThread(ScopedThread const&) = delete;
   ScopedThread& operator=(ScopedThread const&) = delete;
};


#endif // SCOPED_THREAD_H
