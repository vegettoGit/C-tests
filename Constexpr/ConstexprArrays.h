#ifndef CONSTEXPR_ARRAYS_H
#define CONSTEXPR_ARRAYS_H


class TestArrays1
{
	static constexpr char* m_strings[]
	{
		"First",
		"Second",
		"Third"
	};

public:

	void PrintTest();
};

class TestArrays2
{
	static const char* const m_strings[];

public:

	void PrintTest();
};

#endif // ! CONSTEXPR_ARRAYS_H

