#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>


size_t MyStrlen(const char* string)
{
	assert(string);
	size_t length = 0;
	while (*string++)
	{
		length++;
	}
	return length;
}
int main()
{
	printf("%u\n", MyStrlen("hahahahahha"));
	return 0;
}