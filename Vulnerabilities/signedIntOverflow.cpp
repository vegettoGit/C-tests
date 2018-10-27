#include "limits.h"
#include <string.h>

int main(void)
{
	constexpr int lengthSample = 256;     // 2 ^ 8
	constexpr int maxLength    = INT_MAX; // 2 ^ 31  -1

	constexpr int length1 = maxLength;
	constexpr int length2 = lengthSample;

	//char buffer1[length1];
	//char buffer [length2];

	int test = length1 + length2; // Becomes negative

	if (test <= lenghtSample)
	{
		// Boom!
		//memcpy(buffer, buffer1, length1);
	}
}