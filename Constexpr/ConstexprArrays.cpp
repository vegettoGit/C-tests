
#include "ConstexprArrays.h"

#include <iostream>

void TestArrays1::PrintTest()
{
	std::cout << m_strings[1];
}

const char* const TestArrays2::m_strings[]
{
	"First",
	"Second",
	"Third"
};

void TestArrays2::PrintTest()
{
	std::cout << m_strings[1];
}

