#include "JoiningThread.h"

JoiningThread::JoiningThread(std::thread resourceThread) noexcept
   : m_thread(std::move(resourceThread))
{
}

JoiningThread::JoiningThread(JoiningThread&& other) noexcept
   : m_thread(std::move(other.m_thread))
{
}

JoiningThread& JoiningThread::operator=(JoiningThread&& other) noexcept
{
   if (joinable())
   {
      join();
   }
   m_thread = std::move(other.m_thread);
   return *this;
}

JoiningThread& JoiningThread::operator=(std::thread other) noexcept
{
   if (joinable())
   {
      join();
   }
   m_thread = std::move(other);
   return *this;
}

JoiningThread::~JoiningThread() noexcept
{
   if (joinable())
   {
      join();
   }
}

void JoiningThread::swap(JoiningThread& other) noexcept
{
   m_thread.swap(other.m_thread);
}

std::thread::id JoiningThread::get_id() const noexcept
{
   return m_thread.get_id();
}

bool JoiningThread::joinable() const noexcept
{
   return m_thread.joinable();
}

void JoiningThread::join()
{
   m_thread.join();
}

void JoiningThread::detach()
{
   m_thread.detach();
}

std::thread& JoiningThread::as_thread() noexcept
{
   return m_thread;
}

const std::thread& JoiningThread::as_thread() const noexcept
{
   return m_thread;
}
