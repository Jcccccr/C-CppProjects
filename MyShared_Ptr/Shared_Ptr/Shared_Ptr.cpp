#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

//最终版本： 还是针对于智能指针的拷贝的问题解决，采用了引用计数解决拷贝的析构上的问题

//针对智能指针在析构的时候的问题涉及的不同的内存开辟，就要针对性的释放空间   使用仿函数
template<class T>
class Delete
{
public:
	void operator()(T* ptr)
	{
		delete ptr;
		ptr = NULL;
	}
};
//释放动态数组的空间  使用
template<class T>
class DeleteArray
{
public:
	void operator()(T* ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
};

template<class T>
class Free
{
public:
	void operator()(T* ptr)
	{
		free(ptr);
		ptr = NULL;
	}
};

// 这个是针对于文件打开之后没有关闭而产生的错误
template<class T>
class Fclose
{
	void operator()(T* ptr)    //T类型的文件句柄
	{
		fclose(ptr);
	}
};

template<class T,class Del>
class Shared_Ptr
{
private:
	T* _Ptr;
	int* _refCount;
	Del _delete;
public:
	Shared_Ptr(T* Ptr=NULL)
		:_Ptr(Ptr)
		,_refCount(new int(1))
	{
		cout << "Shared_Ptr()" << endl;
	}
	Shared_Ptr(Shared_Ptr& s)
	{
		_Ptr = s._Ptr;
		_refCount = s._refCount;
		(*_refCount)++;
		cout << "Shared_Ptr(Shared_Ptr)" << endl;
	}
	Shared_Ptr<T,Del>& operator=(Shared_Ptr<T,Del>& s)
	{
		if (this != &s)
		{
			if (this->_Ptr)
			{
				if (!--(*_refCount))      //注意這里对引用计数的判断       注意引用计数最好用前置，后置容易出错
				{
					_delete(_Ptr);
					delete _refCount;
					_Ptr = NULL;
					_refCount = NULL;
				}
			}
			_Ptr = s._Ptr;
			_refCount = s._refCount;
			(*_refCount)++;                      //忘掉了增加引用计数
		}
		return *this;
	}
	T& operator*()
	{
		return *_Ptr;
	}
	T* operator->()
	{
		return _Ptr;
	}
	~Shared_Ptr()
	{
		if (!--(*_refCount))      
		{
			_delete(_Ptr);
			delete _refCount;
			_Ptr = NULL;
			_refCount = NULL;                        //每次在使用引用计数的时候都会把refcount的释放忘掉
			cout << "~Shared_Ptr()" << endl;
		}
	}
	T* GetPtr()   const   //注意使用const修饰  下面在调用的时候是const修饰的对象
	{
		return _Ptr;
	}
};

//不会增加Shared_Ptr引用计数的智能指针Weak_Ptr
template <class T>
class Weak_Ptr
{
private:
	T* _Ptr;
public:
	Weak_Ptr()
		:_Ptr(NULL)
	{}
	Weak_Ptr(const Shared_Ptr<T,Delete<T>>& s)         //這里的意义是不增加Shared_Ptr的引用计数
	{
		_Ptr = s.GetPtr();               //非同类对象是无法互相访问成员的
	}
	//Weak_Ptr<T>& operator=(const Shared_Ptr<T, Delete<T>>& s)         //這里的意义是不增加Shared_Ptr的引用计数
	//{
	//	
	//	_Ptr = s.GetPtr();
	//}
	T& operator*()
	{
		return *_Ptr;
	}
	T* operator->()
	{
		return _Ptr;
	}
	//注意Weak_Ptr不需要析构函数 释放空间是交给Shared_Ptr去做的事情
};


//Shared_Ptr的问题：循环引用问题
//场景：  创建一个结构体类型  里面有两个可以指向改结构体对象的指针
struct PtrNode
{
	Shared_Ptr<PtrNode, Delete<PtrNode>> _next;
	Shared_Ptr<PtrNode, Delete<PtrNode>> _prev;
	//Weak_Ptr<PtrNode> _next;
	//Weak_Ptr<PtrNode> _prev;
	~PtrNode()
	{
		cout << "~PtrNode()" << endl;
	}
};

void TestWeakPtr()
{
	//创建两个PtrNode结点
	Shared_Ptr<PtrNode, Delete<PtrNode>> ps1 = new PtrNode;
	Shared_Ptr<PtrNode, Delete<PtrNode>> ps2 = new PtrNode;
	ps1->_next = ps2;
	ps2->_prev = ps1;
	//虽然没有报错但是实际上已经发生了内存泄漏
	//解决方案： 创建一个Weak_Ptr
}


//定制删除器
void TestDiffTypes()
{
	Shared_Ptr<int,Delete<int>> S1(new int(10));
	cout << *S1 << endl;
	Shared_Ptr<string, DeleteArray<string>> S2(new string[10]);
	//Shared_Ptr<string> S2(new string[10]);
}
//void TestShared()
//{
//	Shared_Ptr<int, Delete<int>> S1(new int(10));
//	cout << *S1 << endl;
//	Shared_Ptr<int, Delete<int>> S2(S1);
//	cout << *S1 << endl;
//	cout << *S2 << endl;
//	Shared_Ptr<int, Delete<int>> S3(S2);
//	*S3 = 20;
//	cout << *S3 << endl;
//	Shared_Ptr<int, Delete<int>> S4 = S3;
//	cout << *S4 << endl;
//	Shared_Ptr<string, Delete<int>> S5(new string("hahhahahaha"));
//	cout << *S5 << endl;
//}

int main()
{
	//TestShared();
	//TestDiffTypes();
	TestWeakPtr();
	return 0;
}