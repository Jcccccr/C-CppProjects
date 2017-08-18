#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
//模拟实现字符串拼接
char* MyStrcat(char* dst, const char* src)
{
	char* string = dst;
	assert(dst);
	assert(src);
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return string;s
}
int main()
{
	char str[40] = { 0 };
	char* ptr = "hello";
	MyStrcat(str, ptr);
	MyStrcat(str, "world");
	printf("%s\n", str);
	return 0;
}