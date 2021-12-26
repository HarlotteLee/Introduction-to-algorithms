//优先级队列
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

typedef struct priority_queue_type* priority_queue;
struct priority_queue_type
{
	int heap_size;
	void** array;
	int (*comp)(const void*, const void*);
};

int parent(int i)
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

void heapify(priority_queue pq, int i)
{
	int left = left_child(i);
	int right = right_child(i);
	int largest = i;
	if (left < pq->heap_size && pq->comp(pq->array[largest],pq->array[left]) < 0)
	{
		largest = left;
	}
	if (right < pq->heap_size && pq->comp(pq->array[largest], pq->array[right]) < 0)
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(&pq->array[i], &pq->array[largest], sizeof(void*));
		heapify(pq, largest);
	}
}

void fix_up(priority_queue pq, int i)
{
	while (i > 0 && pq->comp(pq->array[parent(i)], pq->array[i]) < 0) {
		swap(&pq->array[parent(i)], &pq->array[i], sizeof(void*));
		i = parent(i);
	}
}
priority_queue priority_queue_create(int n_length,
	int (*comp) (const void*, const void*))
{
	priority_queue pq = malloc(sizeof(struct priority_queue_type));
	pq->array = malloc(sizeof(void*) * n_length);
	pq->heap_size = 0;
	pq->comp = comp;
	return pq;
}
void* priority_queue_top(priority_queue pq)
{
	return pq->array[0]
}
/*去掉并返回堆的第一个元素 */
void* priority_queue_extract_top(priority_queue pq)
{
	swap(&pq->array[0], &pq->array[pq->heap_size - 1], sizeof(void*));
	--pq->heap_size;
	heapify(pq, 0);
	return pq->array[pq->heap_size];
}
/*把元素 key 插入队列 */
void priority_queue_insert(priority_queue pq, void* key)
{
	++pq->heap_size;
	int i = pq->heap_size - 1;
	memcpy(&pq->array[i], &key, sizeof(void*));
	fix_up(pq, i);
}
bool priority_queue_is_empty(priority_queue pq)
{
	return pq->heap_size == 0;
}
void priority_queue_destroy(priority_queue pq, void (*free_key) (void*))
{
	while (!priority_queue_is_empty(pq)) {
		void* p = priority_queue_extract_top(pq);
		free_key(p);
	}
	free(pq->array);
	free(pq);
}
int cmp_int(const void* p1, const void* p2)
{
	const int* pa = p1;
	const int* pb = p2;
	if (*pa < *pb)
		return -1;
	if (*pa == *pb)
		return 0;
	return 1;
}
int main()
{
	priority_queue pq = priority_queue_create(10, cmp_int);
	for (int i = 0; i < 10; i++) {
		int* p = malloc(sizeof(int));
		*p = i;
		priority_queue_insert(pq, p);
	}
	printf("最大堆结果:\n");
	while (!priority_queue_is_empty(pq)) {
		int* p = priority_queue_extract_top(pq);
		printf("%d ", *p);
		free(p);
	}
	printf("\n");
	priority_queue_destroy(pq, free);
	return 0;
}
