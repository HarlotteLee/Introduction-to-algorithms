#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;
 
void bucket_sort(float *datas,size_t length)
{
     int i,j;
     int index;
     float fvalue;
     size_t lsize;
     list<float> *retlist = new list<float>[length];
     list<float>::iterator iter;
     list<float>::iterator prioiter,enditer;
 
     for(i=0;i<length;++i)
     {
        index = static_cast<int>(datas[i]*10);
        
        retlist[index].push_back(datas[i]);
        lsize = retlist[index].size();
        if(lsize > 1)
        {
           
            iter = --retlist[index].end();
            fvalue = *iter;
            enditer = --retlist[index].begin();
            
            while(iter != enditer)
            {
                
                prioiter = --iter;
                
                iter++;
                
                if(*(prioiter) - *iter > 0.000001)
                {
                    float temp = *(prioiter);
                    *(prioiter) = *iter;
                    *iter = temp;
                }
                iter--;
            }
            
            *(++iter) = fvalue;
        }
     }
     
     j=0;
     for(int i=0;i<length;i++)
     {
         for(iter = retlist[i].begin();iter!=retlist[i].end();++iter)
            datas[j++] = *iter;
     }
     delete [] retlist;
}
 
int main()
{
    float datas[10] = {0.78f,0.17f,0.39f,0.76f,0.23f,0.67f,0.48f,0.58f,0.92f,0.12f};
    bucket_sort(datas,10);
    cout<<"After bucket_sort the result is:"<<endl;
    for(int i=0;i<10;i++)
        cout<<datas[i]<<" ";
    cout<<endl;
    exit(0);
}
