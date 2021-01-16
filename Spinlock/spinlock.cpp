#include "spinlock.h"

void Spinlock::lock()
{
	while (m_atomicFlag.test_and_set(std::memory_order_acquire));
}

void Spinlock::unlock()
{
	m_atomicFlag.clear(std::memory_order_release);
}
