#ifndef SINGLETON_H
#define SINGLETON_H

#include <atomic>
#include <mutex>

class singletonStaticInitializer
{
   singletonStaticInitializer()  = default;
   ~singletonStaticInitializer() = default;

   singletonStaticInitializer(const singletonStaticInitializer&)            = delete;
   singletonStaticInitializer(singletonStaticInitializer&&)                 = delete;
   singletonStaticInitializer& operator=(const singletonStaticInitializer&) = delete;
   singletonStaticInitializer& operator=(singletonStaticInitializer&&)      = delete;
 
public:

   static singletonStaticInitializer* getInstance();
};

class singletonSequentiallyConsistentAtomics
{
   singletonSequentiallyConsistentAtomics()  = default;
   ~singletonSequentiallyConsistentAtomics() = default;

   singletonSequentiallyConsistentAtomics(const singletonSequentiallyConsistentAtomics&)            = delete;
   singletonSequentiallyConsistentAtomics(singletonSequentiallyConsistentAtomics&&)                 = delete;
   singletonSequentiallyConsistentAtomics& operator=(const singletonSequentiallyConsistentAtomics&) = delete;
   singletonSequentiallyConsistentAtomics& operator=(singletonSequentiallyConsistentAtomics&&)      = delete;

   static std::atomic<singletonSequentiallyConsistentAtomics*> m_instance;
   static std::mutex m_mutex;

public:

   static singletonSequentiallyConsistentAtomics* getInstance();
   static void destroyInstance();
};

#endif // SINGLETON_H
