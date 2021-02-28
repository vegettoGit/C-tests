#include "ScopedThread.h"

ScopedThread::ScopedThread(std::thread resourceThread)
   : m_resourceThread(std::move(resourceThread))
{
   if (!m_resourceThread.joinable())
   {
      throw std::logic_error("No thread");
   }
}
ScopedThread::~ScopedThread()
{
   m_resourceThread.join();
}

