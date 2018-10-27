
#define _CRT_SECURE_NO_WARNINGS

#include <string>

int main()
{
	char src[10];
	strcpy(src, "Hello World");

	size_t length = strlen(src);

	int index = length - 1;

	while (src[index] != ':')
	{
		src[index] = '\0';
		index--;
	}

}