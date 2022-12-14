#include "SequentialConsistency.h"
#include <assert.h>

int main()
{
	SequentialConsistency test;

	std::thread a(&SequentialConsistency::writeX, &test);
	std::thread b(&SequentialConsistency::writeY, &test);
	std::thread c(&SequentialConsistency::readXThenY, &test);
	std::thread d(&SequentialConsistency::readYThenX, &test);
	
	a.join();
	b.join();
	c.join();
	d.join();
	
	assert(test.m_z.load() != 0);

	return 0;
}
