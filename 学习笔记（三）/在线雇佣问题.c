//在线雇佣问题
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<limits.h>

int on_line_maximum(int A[], int n, int k)
{
	int best_score = -INT_MAX;
	for (int i = 0; i < k; i++)
	{
		if (A[i] > best_score)
		{
			best_score = A[i];
		}
	}
	for (int i = k; i < n; i++)
	{
		if (A[i] > best_score)
		{
			return i;
		}
	}
	return n - 1;
}
int main()
{
	srand((unsigned)time(NULL));
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 100;
	}
	int n = on_line_maximum(a, 10, 10 / exp(1.0));
	//测试n是不是最好的
	bool flag = true;
	for (int i = 0; i < 10; i++)
	{
		if (a[i] > a[n])
		{
			flag = false;
		}
	}
	printf("%s\n", flag ? "true" : "false");
	return 0;
}
