#define _CRT_SECURE_NO_WARNINGS 1

//C面试重点：内存拷贝（解决覆盖错误）memmove
#include<stdio.h>
#include<assert.h>
//为了避免内存覆盖产生的错误
void* MyMemmove(void* dst,const void* src ,size_t length)
{
	assert(dst);
	if (src == NULL)
		return dst;
	char* ddst = (char*)dst;
	char* ssrc = (char*)src;
	--length;
	size_t len = length;
	while (length)
		*(ddst + len--) = *(ssrc + length--);
	*ddst = *ssrc;
	return dst;
}
int main()
{
	char str[] = "memmove can be very useful......";
	MyMemmove(str + 20, str + 15, 11);                      //在传参数的时候不需要进行类型转换，但是在接收函数的返回值的时候就必须要进行强转，void*可以转换为任意类型、任意类型不能转换为void类型
	puts(str);
	return 0;
}