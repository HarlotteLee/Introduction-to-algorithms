#include<stdio.h>

//自己写的数组交换函数 
void swap(int A[], int i, int j)
{
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

//堆的构造，输入构造点和数组长度 
void heapify(int A[], int i, int n)
{
	//左右子节点 
	int l = i * 2;
	int r = i * 2 + 1;

	//寻找三个结点中最大的结点 
	int largest = i;
	if (l <= n - 1 && A[l] > A[largest])
		largest = l;
	if (r <= n - 1 && A[r] > A[largest])
		largest = r;

	//将最大的元素置为堆顶，并递归执行 
	if (i != largest)
	{
		swap(A, i, largest);
		heapify(A, largest, n);
	}
}

//构建堆 
void build_heap(int A[], int n)
{
	for (int i = n / 2; i >= 0; --i)
		heapify(A, i, n);
}

//堆排序 
void heapsort(int A[], int n)
{
	//先初始化堆 
	build_heap(A, n);


	//通过循环一次将数组第一位排出 
	for (int i = n - 1; i > 0; i--)
	{
		swap(A, 0, i);
		heapify(A, 0, i);
	}
}

/*******下面是优先队列部分*******/
/*以最大优先队列为基础*/

//仅返回队列中最大的元素
int max_mum(int A[])
{
	return A[0];
}

//返回队列中最大的元素，并且在队列中删除该元素
int extract_max(int A[], int n)
{
	if (n < 1)
	{
		printf("数组空，没最大");
		return -1;
	}

	int max = A[1];
	n--;

	heapify(A, n, 0);
	return max;
}

//增加i的值到key(只能增加，减小的话可以改下条件)
void increase_key(int A[], int i, int key)
{
	if (key < A[i])
	{
		printf("更改的值小于原来的值");
		return;
	}
	A[i] = key;
	while (i > 0 && A[i / 2] < A[i])
	{
		swap(A, i, i / 2);
		i = i / 2;
	}
}

//插入一个元素
int insert(int A[], int key, int n)
{
	n++;
	A[n] = -10086;
	increase_key(A, n, key);

	//返回改变后的队列长度 
	return n;
}

/**************over**************/

int main()
{
	int tree[] = { 2, 5, 3, 1, 10, 4 };
	int n = 6;
	heapsort(tree, n);
	for (int i; i < n; i++)
	{
		printf("%d ", tree[i]);
	}

	return 0;
}
