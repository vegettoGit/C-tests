#include "spinlock.h"

int main()
{
	Spinlock spinlock;
	spinlock.lock();
	spinlock.unlock();

	return 0;
}
