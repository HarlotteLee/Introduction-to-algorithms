//随机算法
//通过原地排列产生随机产生排列数组
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void swap(void* a, void* b, size_t elem_size)
{
	if (a == NULL || b == NULL || a == b)
	{
		return;
	}
	char temp[elem_size];//变长数组
	memcpy(temp, a, elem_size);
	memcpy(a, b, elem_size);
	memecpy(b, temp, elem_size);
}
void randomized_in_place(void *array, size_t elem_size, int length)
{
	char *carry = array;
	for (int i = 0; i < length; i++)
	{
		int rand_index = rand() % (length - i) + i;
		swap(&carry[i*elem_size], &carry[rand_index *elem_size], elem_size);
	}
}
void rabdomized_hire_assistant(int A[], int n)
{
	randomized_in_place(A, sizeof(int), n);
	int best = 0;
	printf("hire:");
	for (int i = 0; i < n; i++)
	{
		if (A[i] > best)
		{
			best - A[i];
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
		a[i] = i;
	}
	randomized_hire_assistant(a, 10);

	return 0;
}
