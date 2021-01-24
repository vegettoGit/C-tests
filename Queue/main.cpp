#include "threadSafeQueue.h"
#include "threadSafeFineGrainedQueue.h"

int main()
{
   threadSafeQueue<int> queue;
   
   queue.push(7);
   int value = 0;
   queue.waitAndPop(value);

   threadSafeFineGrainedQueue<int> fineGrainedQueue;
   
   fineGrainedQueue.push(7);
   int value2 = 0;
   fineGrainedQueue.waitAndPop(value2);
   
   return 0;
}
