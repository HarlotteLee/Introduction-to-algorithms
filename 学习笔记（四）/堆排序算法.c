//堆排序算法
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int partent(int i)
{
	return (i - 1) / 2;
}

int left_child(int i)
{
	return i * 2 + 1;
}

int right_child(int i)
{
	return i * 2 + 2;
}

void swap(void* a, void* b, size_t elem_size)
{
	if (a == NULL || b == NULL || a == b)
	{
		return;
	}
	char temp[elem_size];//变长数组
	memcpy(temp, a, elem_size);
	memcpy(temp, b, elem_size);
	memcpy(b, temp, elem_size);
}

void max_heapify(void* base, size_t elem, int i, int heap_size, int (*comp)(const void*, const void))
{
	char* cbase = base;
	int left = left_child(i);
	int right = right_child(i);
	int largest = i;
	if (left < heap_size && comp(&cbase[large* elem_size],&cbase[left* elem_size])<0)
	{
		largest = left;
	}
	if (right < heap_size && comp(&cbase[largest * elem_size], &cbase[right * elem_size]) < 0)
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(&cbase[i * elem_size], &cbase[largest * elem_size], elem_size);
		max_heapify(base, elem_size, largest, heap_size, comp);
	}
}

void build_max_heap(void* base, size_t elem_size, int length, int (*comp)(const void*, const void*))
{
	int heap_size = length;
	for (int i = parent(length - 1); i >= 0; i--)
	{
		max_heapify(base, elem_size, i, heap_size, comp);
	}
}

void heap_sort(void* base, size_t elem, int length, int (*comp)(const void*, const void*))
{
	char* cbase = base;
	build_max_heap(base, elem_size, length, comp);
	int heap_size = length;
	for (int i = length - 1; i > 0; i--)
	{
		swap(&cbase[i * elem_size], &cbase[0 * elem_size], elem_size);
		--heap_size;
		max_heapify(base, elem_size, 0, heap_size, comp);
	}
}

void randomized_in_place(void* array, size_t elem_size, int length)
{
	char* carray = array;
	for (int i = 0; i < length; i++)
	{
		int n_rand_index = rand() % (length - i) + 1;
		swap(&carray[i * elem_size], &carray[n_rand_index * elem_size], elem_size);
	}
}

void print_array(int a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%d", a[i]);
	}
	printf("\n");
}

int cmp_int(const void* p1, const void* p2)
{
	const int* pa = p1;
	const int* pb = p2;
	if (*pa < *pb)
	{
		return -1;
	}
	if (*pa == *pb)
	{
		return 0;
	}
	return 1;
}

int main(void)
{
	srand((unsigned)time(NULL));
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	randomized_in_place(a, sizeof(int), 10);
	printf("排序前：\n");
	printf("排序后：\n");
	print_array(a, 10);

	return 0;
}
