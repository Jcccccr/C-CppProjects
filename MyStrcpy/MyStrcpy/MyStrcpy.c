#define _CRT_SECURE_NO_WARNINGS 1
//模拟实现C库函数strcpy
//注意无须考虑增容，因为库函数里面的strcpy的前提就是dst的空间足够大
#include<stdio.h>
#include<assert.h>

char* MyStrcpy(char* dst, const char* src)    //注意返回值
{
	char* string = dst;
	assert(dst);
	assert(src);
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return string;
}
void TestMyStrcpy()
{
	char str1[] = "HelloWorld";
	char str2[20];
	MyStrcpy(str2, str1);
	printf("%s\n", str2);
}
int main()
{
	TestMyStrcpy();
	return 0;
}