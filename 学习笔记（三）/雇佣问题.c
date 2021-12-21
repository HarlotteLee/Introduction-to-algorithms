//雇佣问题
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void hire_assistant(int A[], int n)
{
	int best = 0;
	printf("hire:");
	for (int i = 0; i < n; i++)
	{
		if (A[i] > best)
		{
			best = A[i];
			printf("%d", i);
		}
	}
	printf("\n");
}
int main()
{
	srand((unsigned)time(NULL));
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 100;
		printf("%d  ", a[i]);
	}
	printf("\n");
	hire_assistant(a, 10);

	return 0;
}
