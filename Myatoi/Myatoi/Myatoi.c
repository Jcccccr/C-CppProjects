#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
#include<ctype.h>
//  将字符转换为整形     模拟atoi    易错点：考虑溢出问题
int My_atoi(const char* str)
{
	int flag = 1;           //符号标志为
	int symbol = 1;
	//处理非法输入
	if (str == NULL)
		return 0;
	//处理空格和Tab
	while (isspace(*str))
	{
		str++;
	}
	//处理+-符号
	if (*str == '-')
	{
		flag = -1;
		str++;
		if ((*str)<'0' || (*str)>'9')
		{
			symbol = 0;
			return 0;
		}
	}
	if (*str == '+')
		str++;
	while (*str == '0')
	{
		str++;
	}
	if ((*str)<'0' || (*str)>'9')
	{
		symbol = 0;
		return 0;
	}
	//正式处理字符串转换为正数
	int num = 0;	while ((*str) && (*str) >= '0' && (*str) <= '9')
	{
		num = num * 10 + (*str - '0');              //注意這个算法 可以将字符串转换为整形
		str++;
	}
	//考虑求的值是否溢出  分为正数溢出和负数溢出
	if (((num > 0x7fffffff) && (flag == 1)) ||
		(num < (signed int)0x80000000) && (flag == -1))
	{
		return 0;
	}
	return num;
}
int main()
{
	int num = My_atoi("  1233445");
	printf("%d\n", num);
	return 0;
}