#pragma once
#include<iostream>

using namespace std;
//树表查找结构的类

template<typename DataType>
struct BiNode
{
	DataType data;
	BiNode* lchild;
	BiNode* rchild;
};

//二叉排序树
//为了外部调用共有函数时简洁，例如：查找5，只用写SearchBST（5）
class BiSortTree
{
public:
	BiSortTree(int a[], int n);   //建立集合a[n]的二叉排序树
	~BiSortTree() { Release(root); }  //同二叉链表的析构函数
	void InOrder() { InOrder(root); }

	BiNode<int>* InsertBST(int x) { return InsertBST(root, x); }  //插入记录x
	void DeleteBST(BiNode<int>* p, BiNode<int>* f);  //删除f的左孩子p
	BiNode<int>* SearchBST(int k) { return SearchBST(root, k); }   //查找值为k的结点
public:
	void InOrder(BiNode<int>* bt);
	BiNode<int>* InsertBST(BiNode<int>* bt, int x);
	BiNode<int>* SearchBST(BiNode<int>* bt, int k);
	void Release(BiNode<int>* bt);     //析构函数的调用，同二叉链表类
	BiNode<int>* root;          //二叉排序树的根指针
};

#pragma once
//开放定址法
const int MaxSize = 100;

class HashTable1
{
public:
	HashTable1();   //构造函数初始化空的散列表 
	~HashTable1(){}    //析构函数为空
	int Insert(int k);  //插入
	int Delete(int k);   //删除
	int Search(int k);   //查找
private:
	int H(int k);    //散列函数
	int ht[MaxSize];    //闭散列表H(key)=key mod 11  线性探测法构造闭散列表(H(key)+1) mod 11   (H(key)+2) mod 11
	                       //减少堆积    平方探测法构造闭散列表(H(key)+1^2) mod 11  (H(key)-1^2) mod 11
};

#pragma once
//拉链法
template<typename DataType>
struct Node
{
	int data;
	Node* next;
};

const int MaxSize = 100;

class HashTable2
{
public:
	HashTable2();   //构造函数，初始化开散列表
	~HashTable2();   //析构函数，释放同义词字表结点
	int Insert(int k);  //插入
	int Delete(int k);   //删除
	Node<int>* Search(int k);    //查找
private:
	int H(int k);   //散列函数
	Node<int>* ht[MaxSize];   //开散列表

};

#pragma once
//线性查找结构的类定义

const int MaxSize = 100;

class LineSearch
{
public:
	LineSearch(int a[], int n);      //构造函数
	~LineSearch() {}                 //析构函数为空
	int SeqSearch(int k);            //顺序查找
	int BinSearch1(int k);           //折半非递归查找
	int BinSearch2(int low, int high, int k);    //折半递归查找
private:
	int data[MaxSize];               //查找集合为整形
	int length;                      //查找集合的元素个数
};

#include "BiSortTree.h"

BiSortTree::BiSortTree(int a[], int n)
{
	root = nullptr;
	for (int i = 0; i < n; i++)
	{
		root = InsertBST(root, a[i]);
		cout << root->data << "  ";
	}
}

void BiSortTree::DeleteBST(BiNode<int>* p, BiNode<int>* f)
{
	if ((p->lchild == nullptr) && (p->rchild == nullptr))//当要删除的结点没有左孩子也没有右孩子
	{
		f->lchild = nullptr;
		delete p;
		return;   //p为叶子
	}
	else if (p->lchild == nullptr)//当要删除的结点只有右子树时
	{
		f->lchild = p->rchild;
		delete p;
		return;
	}
	else if (p->rchild == nullptr)//当要删除的结点只有左子树时
	{
		f->lchild = p->lchild;
		delete p;
		return;
	}
	else
	{
		BiNode<int>* par = p;
		BiNode<int>* s = p->rchild;//找p右子树中最小的元素代替p的值，最后删掉那个最小的元素
		while (s->lchild != nullptr)
		{
			par = s;
			s = s->lchild;
		}
		p->data = s->data;
		if (par == p)//特殊情况，p的右子树没有左子树
			par->rchild = s->rchild;
		else
			par->lchild = s->rchild;
		delete s;
	}
}

void BiSortTree::InOrder(BiNode<int>* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		InOrder(bt->lchild);
		cout << bt->data << " ";
		InOrder(bt->rchild);
	}
}

BiNode<int>* BiSortTree::InsertBST(BiNode<int>* bt, int x)
{
	if (bt == nullptr)
	{
		BiNode<int>* p = new BiNode<int>;
		p->data = x;
		p->lchild = nullptr;
		p->rchild = nullptr;
		bt = p;
		return bt;
	}
	else if (x < bt->data)
		return bt->lchild = InsertBST(bt->lchild, x);
	else
		return bt->rchild = InsertBST(bt->rchild, x);
}

BiNode<int>* BiSortTree::SearchBST(BiNode<int>* bt, int k)
{
	if (bt == nullptr)
		return nullptr;
	if (k < bt->data)
		return SearchBST(bt->lchild, k);
	else if (k > bt->data)
		return SearchBST(bt->rchild, k);
	else
		return bt;
}

void BiSortTree::Release(BiNode<int>* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		Release(bt->lchild);//释放左子树
		Release(bt->rchild);//释放右子树
		delete bt;//释放根节点
	}
}
#include "HashTable1.h"

HashTable1::HashTable1()
{
	for (int i = 0; i < MaxSize; i++)
	{
		ht[i] = 0;      //0表示该散列单元为空
	}
}

int HashTable1::Insert(int k)
{
	return 0;
}

int HashTable1::Delete(int k)
{
	return 0;
}

int HashTable1::Search(int k)
{
	int i;
	int j = H(k);  //计算散列地址
	i = j;
	while (ht[i] != 0)
	{
		if (ht[i] == k)
			return i;    //查找成功
		else
			i = (i + 1) % MaxSize;   //向后探测一个位置
	}
	return -1;    //查找失败
}

int HashTable1::H(int k)
{
	return 0;
}
#include "HashTable2.h"

HashTable2::HashTable2()
{
	for (int i = 0; i < MaxSize; i++)
	{
		ht[i] = nullptr;
	}
}

HashTable2::~HashTable2()
{
	Node<int>* p = nullptr;
	Node<int>* q = nullptr;

	for (int i = 0; i < MaxSize; i++)
	{
		p = q = ht[i];
		while (p != nullptr)
		{
			p = p->next;
			delete q;
			q = p;
		}
	}
}

int HashTable2::Insert(int k)
{
	return 0;
}

int HashTable2::Delete(int k)
{
	return 0;
}

Node<int>* HashTable2::Search(int k)
{
	int j = H(k);    //计算散列地址
	Node<int>* p = ht[j];   //工作指针p初始化
	while (p != nullptr)
	{
		if (p->data == k)
			return p;
		else
			p = p->next;
	}
	return nullptr;   //查找失败
}

int HashTable2::H(int k)
{
	return 0;
}
#include "LineSearch.h"

LineSearch::LineSearch(int a[], int n)
{
	for (int i = 0; i < n; i++)
		data[i + 1] = a[i];      //查找集合从下标1开始存放
	length = n;
}

//顺序查找  设置哨兵  哨兵就是待查值  放置在下标为0处
//不用判断查找位置是否越界，提高查找速度，查找不成功的话，i的值为0
//时间复杂度O(n)
int LineSearch::SeqSearch(int k)
{
	int i = length;      //从数组的最高端开始比较
	data[0] = k;         //设置哨兵
	while (data[i] != k)
		i--;
	return i;
}

//折半查找的非递归算法
//假设有序表按关键码升序排列，取中间值为比较对象，若小于则在左半区查找，如果大于则在右半区查找
//时间复杂度O(log n)
int LineSearch::BinSearch1(int k)
{
	int mid, low = 1, high = length;   //初始的查找空间是[1,n]
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (k < data[mid])
			high = mid - 1;
		else if (k > data[mid])
			low = mid + 1;
		else
			return mid;        //查找成功，返回元素序号
	}
	return 0;                  //查找失败，返回0
}

//折半查找的递归算法
//时间复杂度O(log n)
int LineSearch::BinSearch2(int low, int high, int k)
{
	if (low > high)   //递归的边界条件
		return 0;
	else
	{
		int mid = (low + high) / 2;
		if (k < data[mid])
			BinSearch2(low, mid - 1, k);
		else if (k > data[mid])
			BinSearch2(low + 1, high, k);
		else
			return mid;
	}
}
#include "BiSortTree.h"

int main()
{
	/*BiNode<int>* p = nullptr;

	int arr[10] = { 7,2,3,10,5,6,1,8,9,4 };
	BiSortTree B(arr, 10);


	B.InOrder();

	int key;
	cout << "请输入要查找的元素：";
	cin >> key;

	p = B.SearchBST(key);
	if (p != nullptr)
		cout << p->data << endl;
	else
		cout << "查找失败" << endl;*/

	system("pause");
	return 0;

}
