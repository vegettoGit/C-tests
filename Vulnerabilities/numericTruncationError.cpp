#include "limits.h"
#include <string.h>

int main(void)
{
	constexpr unsigned int lengthSample = 256;
	constexpr unsigned int lengthSample2 = UINT_MAX - lengthSample;

	//char buffer1[lengthSample2];
	//char buffer [lengthSample];

	int length = lengthSample + lengthSample2; // Becomes negative

	if (length <= lengthSample)
	{
		// Boom!
		//memcpy(buffer, buffer1, lengthSample2);
	}
}