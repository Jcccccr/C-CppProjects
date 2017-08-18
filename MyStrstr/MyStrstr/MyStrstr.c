#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
//²éÕÒ×Ó´®

char* MyStrstr(const char* dst, const char* src)
{
	assert(dst);
	if (src == NULL)
		return dst;
	char* cur = dst;
	while (*cur)
	{
		char* psrc = src;
		if (*cur == *src)
		{
			char* tmp = cur;
			while (*tmp == *psrc&&*psrc)
			{
				tmp++;
				psrc++;
			}
			if (*psrc == '\0')
			{
				return cur;
			}
		}
		cur++;
	}
	return NULL;
}
int main()
{
	//if (MyStrstr("hahahha", "ji") == NULL)
		//printf("1\n");
	printf("%x\n", MyStrstr("Hello World", "orl"));
	return 0;
}