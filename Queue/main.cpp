#include "threadSafeQueue.h"

int main()
{
   threadSafeQueue<int> queue;
   
   queue.push(7);
   int value = 0;
   queue.waitAndPop(value);
   
   return 0;
}