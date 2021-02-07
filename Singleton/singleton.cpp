#include "singleton.h"

singletonStaticInitializer* singletonStaticInitializer::getInstance()
{
   static singletonStaticInitializer instance;
   return &instance;
}

std::atomic<singletonSequentiallyConsistentAtomics*> singletonSequentiallyConsistentAtomics::m_instance = nullptr;
std::mutex singletonSequentiallyConsistentAtomics::m_mutex;

// Double checked locking
singletonSequentiallyConsistentAtomics* singletonSequentiallyConsistentAtomics::getInstance()
{
   singletonSequentiallyConsistentAtomics* instance = m_instance.load();
   if (instance == nullptr)
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      instance = m_instance.load();
      if (instance == nullptr)
      {
         instance = new singletonSequentiallyConsistentAtomics();
         m_instance.store(instance);
      }
   }
   return instance;
}

void singletonSequentiallyConsistentAtomics::destroyInstance()
{
   singletonSequentiallyConsistentAtomics* instance = std::atomic_exchange<singletonSequentiallyConsistentAtomics*>(&m_instance, nullptr);
   delete instance;
}
