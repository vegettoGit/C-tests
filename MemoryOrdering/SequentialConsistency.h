#ifndef SEQUENTIAL_CONSISTENCY_H
#define SEQUENTIAL_CONSISTENCY_H

#include <atomic>
#include <thread>

// Inspired by the examples in the book "C++ Concurrency in Action: Practical Multithreading", by Anthony Williams
class SequentialConsistency
{
public:

	void writeX();
	void writeY();
	void readXThenY();
	void readYThenX();
	
	std::atomic<bool> m_x = false;
	std::atomic<bool> m_y = false;
	std::atomic<int>  m_z = 0;
};

#endif // SEQUENTIAL_CONSISTENCY_H
