#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void radix_sort(int *datas,size_t length,size_t digits);
int max(int *A,size_t length);
size_t get_digit_number(int data);
void count_sort(int *A,int *B,size_t length,int k);
size_t get_digit(int data,size_t d);
 
int main()
{
    int i;
    int datas[10] = {432,578,256,782,691,206,942,387,696,374};
    int k = max(datas,10);
    int d = get_digit_number(k);
    radix_sort(datas,10,d);
    printf("After radix sort the result is:\n");
     for(i=0;i<10;i++)
        printf("%d ",datas[i]);
    exit(0);
}
 
void radix_sort(int *datas,size_t length,size_t digits)
{
    int i,j,k;
 
    int *temps = (int*)malloc(sizeof(int)*10);
    int *tmpd = (int*)malloc(sizeof(int)*length);
    int *rets = (int*)malloc(sizeof(int)*length);
    for(i=0;i<digits;i++)
    {
        memset(temps,0,10*sizeof(int));
        memset(tmpd,-1,10*sizeof(int));
        memset(rets,-1,10*sizeof(int));
        for(j = 0;j<length;j++)
            tmpd[j] = get_digit(datas[j],i);
        for(j=0;j<length;j++)
            temps[tmpd[j]] = temps[tmpd[j]] +1;
        for(k=1;k<10;k++)
            temps[k] = temps[k] + temps[k-1];
        for(j=length-1;j>=0;j--)
        {
            rets[temps[tmpd[j]]-1] = datas[j];
            temps[tmpd[j]] = temps[tmpd[j]] -1;
        }
        memcpy(datas,rets,sizeof(int)*length);
    }
    free(temps);
    free(tmpd);
    free(rets);
}
 
int max(int *datas,size_t length)
{
    int k = datas[0];
    int i;
    for(i=1;i<length;++i)
        if(datas[i] > k)
            k = datas[i];
    return k;
}
 
size_t get_digit(int data,size_t d)
{
    int tmp;
    tmp = data;
    while(d)
    {
        tmp /= 10;
        d--;
    }
    return (tmp%10);
}
 
size_t get_digit_number(int data)
{
    int d = 0;
    while(data)
    {
        d = d+1;
        data = data / 10;
    }
    return d;
}
