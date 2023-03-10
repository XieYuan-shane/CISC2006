#include<stdio.h>
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void QuickSort(int* num, int low, int high)
{
    if(high <= low)
        return; 
    int temp = num[low];
    int start = low;
    int end = high;
    while(start != end){
        while(num[start]<=temp && start < end){
            start = start + 1;
        }
        while(num[end]>=temp && start < end){
            end = end - 1;
        }
        if(start < end){
            swap(&num[start],&num[end]);
        }
    }
    swap(&num[low],&num[start]);
    QuickSort(num,low,start-1);
    QuickSort(num,start+1,high);
}
int main(){
    int a[3] = {6,1,2};
    QuickSort(a,0,2);
    for(int i=0;i<3;i++){
        printf("%d ",a[i]);
    }
    return 0;
}