#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>

// Based on the example in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
class Spinlock
{
	std::atomic_flag m_atomicFlag = ATOMIC_FLAG_INIT;

public:
	
	void lock();
	void unlock();
};

#endif // SPINLOCK_H
