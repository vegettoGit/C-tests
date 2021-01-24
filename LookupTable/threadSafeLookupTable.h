#ifndef THREAD_SAFE_LOOKUP_TABLE_H
#define THREAD_SAFE_LOOKUP_TABLE_H

#include <algorithm>
#include <list>
#include <shared_mutex>
#include <vector>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
template<typename Key, typename Value, typename Hash = std::hash<Key>>
class threadSafeLookupTable
{

private:
   
   class bucketType
   {
   
   private:
   
      typedef std::pair<Key, Value> bucketValue;
      typedef std::list<bucketValue> bucketData;
      typedef typename bucketData::iterator bucketIterator;
      typedef typename bucketData::const_iterator bucketConstIterator;

      bucketData m_data;
      mutable std::shared_mutex m_mutex;

      bucketIterator findEntryFor(Key const& key)
      {
         return std::find_if(m_data.begin(), m_data.end(),
            [&](bucketValue const& item)
            {
               return item.first == key; 
            });
      }

      bucketConstIterator findEntryFor(Key const& key) const
      {
         return std::find_if(m_data.begin(), m_data.end(),
            [&](bucketValue const& item)
            {
               return item.first == key;
            });
      }

   public:

      Value valueFor(Key const& key, Value const& defaultValue) const
      {
         std::shared_lock<std::shared_mutex> lock(m_mutex);
         bucketConstIterator const foundEntry = findEntryFor(key);
         return (foundEntry == m_data.end()) ? defaultValue : foundEntry->second;
      }

      void addOrUpdate(Key const& key, Value const& value)
      {
         std::unique_lock<std::shared_mutex> lock(m_mutex);
         bucketIterator foundEntry = findEntryFor(key);
         if (foundEntry == m_data.end())
         {
            m_data.push_back(bucketValue(key, value));
         }
         else
         {
            foundEntry->second = value;
         }
      }

      void remove(Key const& key)
      {
         std::unique_lock<std::shared_mutex> lock(m_mutex);
         bucketConstIterator const foundEntry = findEntryFor(key);
         if (foundEntry != m_data.end())
         {
            m_data.erase(foundEntry);
         }
      }

   };

   std::vector<std::unique_ptr<bucketType>> m_buckets;
   Hash m_hasher;
   
   bucketType& getBucket(Key const& key) const
   {
      std::size_t const bucketIndex = m_hasher(key) % m_buckets.size();
      return *m_buckets[bucketIndex];
   }

   static constexpr unsigned int s_numBuckets = 19;

public:

   threadSafeLookupTable(Hash const& hasher = Hash())
      : m_buckets(s_numBuckets), 
        m_hasher(hasher)
   {
      for (unsigned i = 0; i < s_numBuckets; ++i)
      {
         m_buckets[i].reset(new bucketType);
      }
   }

   threadSafeLookupTable(threadSafeLookupTable const& other) = delete;
   threadSafeLookupTable& operator = (threadSafeLookupTable const& other) = delete;
   
   Value valueFor(Key const& key, Value const& defaultValue = Value()) const
   {
      return getBucket(key).valueFor(key, defaultValue);
   }

   void addOrUpdate(Key const& key, Value const& value)
   {
      getBucket(key).addOrUpdate(key, value);
   }

   void remove(Key const& key)
   {
      getBucket(key).remove(key);
   }

};

#endif // THREAD_SAFE_LOOKUP_TABLE_H
