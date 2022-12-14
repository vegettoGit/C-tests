#include "SequentialConsistency.h"

void SequentialConsistency::writeX()
{
	m_x.store(true, std::memory_order_seq_cst);
}

void SequentialConsistency::writeY()
{
	m_y.store(true, std::memory_order_seq_cst);
}

void SequentialConsistency::readXThenY()
{
	while (!m_x.load(std::memory_order_seq_cst));
	if (m_y.load(std::memory_order_seq_cst))
	{
		++m_z;
	}
}

void SequentialConsistency::readYThenX()
{
	while (!m_y.load(std::memory_order_seq_cst));
	if (m_x.load(std::memory_order_seq_cst))
	{
		++m_z;
	}
}
