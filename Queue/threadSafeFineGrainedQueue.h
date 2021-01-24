#ifndef THREAD_SAFE_FINE_GRAINED_QUEUE_H
#define THREAD_SAFE_FINE_GRAINED_QUEUE_H

template<typename T>
class threadSafeFineGrainedQueue
{

private:

   struct node
   {
      std::shared_ptr<T> data;
      std::unique_ptr<node> next;
   };

   std::mutex m_headMutex;
   std::unique_ptr<node> m_head;
   std::mutex m_tailMutex;
   node* m_tail;
   std::condition_variable m_dataCondition;

   node* getTail()
   {
      std::lock_guard<std::mutex> tailLock(m_tailMutex);
      return m_tail;
   }

   std::unique_ptr<node> popHead()
   {
      std::unique_ptr<node> oldHead = std::move(m_head);
      m_head = std::move(oldHead->next);
      return oldHead;
   }

   std::unique_ptr<node> tryPopHead()
   {
      std::lock_guard<std::mutex> headLock(m_headMutex);
      if (m_head.get() == getTail())
      {
         return std::unique_ptr<node>();
      }
      return popHead();
   }

   std::unique_ptr<node> tryPopHead(T& value)
   {
      std::lock_guard<std::mutex> headLock(m_headMutex);
      if (m_head.get() == getTail())
      {
         return std::unique_ptr<node>();
      }
      value = std::move(*m_head->data);
      return popHead();
   }

   std::unique_lock<std::mutex> waitForData()
   {
      std::unique_lock<std::mutex> headLock(m_headMutex);
      
      m_dataCondition.wait(headLock, [&] 
         {
            return m_head.get() != getTail(); 
         });

      return std::move(headLock);
   }

   std::unique_ptr<node> waitPopHead()
   {
      std::unique_lock<std::mutex> headLock(waitForData());
      return popHead();
   }

   std::unique_ptr<node> waitPopHead(T& value)
   {
      std::unique_lock<std::mutex> headLock(waitForData());
      value = std::move(*m_head->data);
      return popHead();
   }

public:
   
   threadSafeFineGrainedQueue() :
      m_head(new node), 
      m_tail(m_head.get())
   {
   }

   threadSafeFineGrainedQueue(const threadSafeFineGrainedQueue& other) = delete;
   
   threadSafeFineGrainedQueue& operator=(const threadSafeFineGrainedQueue& other) = delete;
   
   std::shared_ptr<T> tryPop()
   {
      std::unique_ptr<node> oldHead = tryPopHead();
      return oldHead ? oldHead->data : std::shared_ptr<T>();
   }

   bool tryPop(T& value)
   {
      std::unique_ptr<node> const oldHead = tryPopHead(value);
      return oldHead;
   }

   std::shared_ptr<T> waitAndPop()
   {
      std::unique_ptr<node> const oldHead = waitPopHead();
      return oldHead->data;
   }
   
   void waitAndPop(T& value)
   {
      std::unique_ptr<node> const oldHead = waitPopHead(value);
   }

   void push(T newValue)
   {  
      std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
      std::unique_ptr<node> p(new node);
      {
         std::lock_guard<std::mutex> tailLock(m_tailMutex);
         m_tail->data = newData;
         node* const newTail = p.get();
         m_tail->next = std::move(p);
         m_tail = newTail;
      }
      m_dataCondition.notify_one();
   }

   bool empty()
   {
      std::lock_guard<std::mutex> headLock(m_headMutex);
      return (m_head.get() == getTail());
   }

};

#endif // THREAD_SAFE_FINE_GRAINED_QUEUE_H
