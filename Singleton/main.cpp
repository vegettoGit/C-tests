#include "singleton.h"

int main()
{
   singletonStaticInitializer* singleton1             = singletonStaticInitializer::getInstance();
   singletonSequentiallyConsistentAtomics* singleton2 = singletonSequentiallyConsistentAtomics::getInstance();

   singletonSequentiallyConsistentAtomics::destroyInstance();

   return 0;
}
