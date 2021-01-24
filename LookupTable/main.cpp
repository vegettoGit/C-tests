#include "threadSafeLookupTable.h"

int main()
{
   threadSafeLookupTable<int, bool> lookupTable;

   lookupTable.addOrUpdate(0, true);

   bool result = lookupTable.valueFor(0);
   lookupTable.remove(0);
   result = lookupTable.valueFor(0);

   return 0;
}
