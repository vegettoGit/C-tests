#define  _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char* buffer = (char*)malloc(sizeof(char) * 10);
	
	strcpy(buffer, argv[1]);

	free(buffer);
}