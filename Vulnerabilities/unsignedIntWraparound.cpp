#include "limits.h"
#include <string.h>

int main(void)
{
	constexpr unsigned int maxUnsignedNumberInOneBytePlusOne = 256;      // 2^8
	constexpr unsigned int maxUnsignedNumberIn4Bytes         = UINT_MAX; // 2^32 - 1

	constexpr unsigned int length1                           = maxUnsignedNumberIn4Bytes;
	constexpr unsigned int length2                           = maxUnsignedNumberInOneBytePlusOne;

	//char buffer1[length1];
	//char buffer [length2];

	unsigned int test                                        = length1 + length2; // Wraps around to 255 (length2 - 1)

	if (test <= maxUnsignedNumberInOneBytePlusOne)
	{
		// Boom!
		//memcpy(buffer, buffer1, length1);
	}
}