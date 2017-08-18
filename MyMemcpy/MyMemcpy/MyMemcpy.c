#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
//模拟实现C库函数memcpy

void* MyMemcpy(void* dst, const void* src,size_t length)
{
	assert(dst);
	assert(src);
	char* ddst = (char*)dst;
	char* ssrc = (char*)src;             //memcpy就是按照字节拷贝 所以在循环赋值前面就进行转换为char*类型
	while (length--)
	{
		*ddst++ = *ssrc++;
	}
	return dst;
}
//-------------test-------------------
struct {
	char name[40];
	int age;
} person, person_copy;
int main()
{
	char myname[] = "Pierre de Fermat";
	/* using memcpy to copy string: */
	MyMemcpy(person.name, myname, strlen(myname) + 1);
	person.age = 46;

	/* using memcpy to copy structure: */
	MyMemcpy(&person_copy, &person, sizeof(person));

	printf("person_copy: %s, %d \n", person_copy.name, person_copy.age);
	return 0;
}