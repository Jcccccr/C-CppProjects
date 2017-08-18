#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
int MyStrcmp(const char* dst, const char* src)
{
	assert(dst);
	assert(src);
	while ((*dst) && (*src))
	{
		if (*dst < *src)
			return -1;
		else if (*dst > *src)
			return 1;
		else
		{
			dst++;
			src++;
		}
	}
	if (*dst == 0 && *src == 0)
		return 0;
	if (*dst)
		return 1;
	else
		return -1;
}
int main()
{
	//int num = MyStrcmp("hahhahhaa", "hahahhaha");
	//int num = MyStrcmp("hello", "hello");
	//int num = MyStrcmp("hell", "hello");
	//int num = MyStrcmp("", "");
	int num = MyStrcmp("hell00000", "hello");
	//int num = MyStrcmp(haha, "hello");
	printf("%d\n", num);
	return 0;
}