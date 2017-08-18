#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<string.h>
//模拟实现itoa函数
//将整数转换为字符串，string是目标字符串   radix是进制数,进制应该是小于26进制的
char* Myitoa(int value , char* string , int radix)
{
	if (radix == 0)  //0进制还需要具体的商酌
		return NULL;
	char indexs[] = "0123456789abcdefghijklmnopqrstuvwxyz";   //建立索引
	char* p = string;
	int i = 0;
	unsigned num = 0;      //用无符号整形临时值存放我们要处理的数字
	if (value < 0)
	{
		*p++ = '-';
		num = (unsigned)-value;        // 将数字部分提取存储于num等待处理
	}
	num = (unsigned)value;
	//放入字符串数组
	while (num)
	{
		*p++ = indexs[num % (unsigned)radix];   //根据不同的进制放不同的数字
		num /= radix;
	}
	*p = 0;
	//逆序字符串
	int k = 0;
	if (string[0] == '-')
		k = 1;
	int start = k;
	int end = strlen(string) - 1;
	char tmp;
	while (start <= end)                 //不要在这里面的内部做自减自增操作  刚开始犯了错误
	{
		tmp = string[start];              
		string[start] = string[end];
		string[end] = tmp;
		start++;
		end--;
	}
	return string;
}
int main()
{
	char str[20] = { 0 };
	Myitoa(1750, str, 2);
	puts(str);
	return 0;
}