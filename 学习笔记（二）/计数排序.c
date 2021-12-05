#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int max(int *A,size_t length);
void count_sort(int *A,int *B,size_t length,int k);
 
int main()
{
    int datas[10] = {2,5,3,0,2,3,0,3,4,6};
    int ret[10];
    int i,k;
    k = max(datas,10);
    printf("max value k = %d\n",k);
    count_sort(datas,ret,10,k);
    printf("After counting sort,the result is:\n");
    for(i=0;i<10;i++)
        printf("%d ",ret[i]);
    exit(0);
}
 
int max(int *A,size_t length)
{
    int k = A[0];
    int i;
    for(i=1;i<length;++i)
        if(A[i] > k)
            k = A[i];
    return k;
}
void count_sort(int *A,int *B,size_t length,int k)
{
    int i,j;
    
    int *C = (int*)malloc(sizeof(int)*(k+1));
   
    memset(C,0,(k+1)*sizeof(int));
   
    for(i=0;i<length;++i)
        C[A[i]] = C[A[i]] + 1;
 
    for(j=1;j<=k;++j)
        C[j] = C[j] + C[j-1];
   
    for(i=length-1;i>=0;i--)
    {
         B[C[A[i]]-1] = A[i];
         C[A[i]] = C[A[i]] - 1;
    }
    free(C);
