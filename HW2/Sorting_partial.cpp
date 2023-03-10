#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include<ctime>
#define random(x)(rand()%x)

using namespace std;

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void InsertionSort(int* num, int n)
{
    for(int i = 0;i < n;i++){
        int temp = num[i];
        int j = i - 1;
        while(j >= 0&& num[j] > temp){
            num[j + 1] = num[j];
            j--;
        }
        num[j + 1] = temp;
    }
}

void BubbleSort(int* num, int n)
{
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n-i-1;j++){
            if(num[j] > num[j + 1]){
                swap(&num[j], &num[j + 1]);
            }
        }
    }
}

void SelectionSort(int* num, int n)
{
    int min;
    for(int i = 0;i < n;i++){
        min = i;
        for(int j = i+1;j < n;j++){
            if(num[j] < num[min]){
                min = j;
            }
        }
        swap(&num[i], &num[min]);
    }
}

void Heap_build(int a[], int root, int length)  // Create heap
{
    int lchild = root*2+1;
    if (lchild < length)
    {
        int max_val = lchild;
        int rchild = lchild+1;
        if (rchild < length)
        {
            if (a[rchild] > a[max_val])  // find the larger value of the two children
            {
                max_val = rchild;
            }
        }
        if (a[root] < a[max_val])  // put the larger value to the parent node
        {
            swap(a[root],a[max_val]);
            Heap_build(a,max_val,length); // recursive fix of the heap-order property
        }
    }
}

void HeapSort(int* a,int len)
{
    for (int i = (len-1)/2; i >= 0; --i) // create heap from the last internal node
    {
        Heap_build(a,i,len);
    }

    for (int j = len-1; j > 0; --j) // j is the length of array (need to reconstruct)
    {
        swap(a[0],a[j]); // put the larger value to the last position of the array
        Heap_build(a,0,j); // remove the element at the last position and rebuild the heap
    }
}

void Merge(int* num, int* L, int lenL, int* R, int lenR)
{
    int l = 0;
    int r = 0;
    for(int i = 0; i < (lenL + lenR); i++){
        if(l >= lenL) {
            num[i] = R[r];
            r++;
            continue;
        }
        else if(r >= lenR) {
            num[i] = L[l] ;
            l++;
            continue;
        }
        else if(L[l] < R[r]){
                    num[i] = L[l];
                    l++;
                    continue;
        }
        else{
            num[i] = R[r];
            r++;
        }
    }
}

void MergeSort(int* num, int n)
{
    if(n <= 1)
    {
        return;
    }
    else{
        int * L = (int*)malloc(sizeof(int) * (n/2));
		int * R = (int*)malloc(sizeof(int) * (n-n/2));
        for(int i = 0;i < n/2;i++)
        {
            L[i] = num[i];
        }
        for(int i = 0;i < n-n/2;i++)
        {
            R[i] = num[i+n/2];
        }
        MergeSort(L,n/2);
        MergeSort(R,n-n/2);
        Merge(num,L,n/2,R,n-n/2);
        free(L);
        free(R);
    }
}

int PickPivot(int* num, int low, int high)  // Pick 3 numbers at random and take the median value
{
    srand((int)time(0));
    int a[3];
	a[0] = num[(rand()%low)+(high)];
    a[1] = num[(rand()%low)+(high)];
    a[2] = num[(rand()%low)+(high)];
    BubbleSort(a,3);
    return a[1];
}

void QuickSort(int* num, int low, int high)
{
    if(high < low)
        return; 
    int temp = num[low];
    int start = low;
    int end = high;
    while(start != end){
        while(num[end]>=temp && start < end){
            end = end - 1;
        }//右边先走
        while(num[start]<=temp && start < end){
            start = start + 1;
        }//左边走
        if(start < end){
            swap(&num[start],&num[end]);
        }
    }
    swap(&num[low],&num[start]);
    QuickSort(num,low,start-1);
    QuickSort(num,start+1,high);
}

void print(int* num, int length)
{
    for(int i = 0; i < length; i++)
        cout << num[i] << " ";
    cout<<endl;
}

int main()
{
    clock_t Start_time, End_time;
    const int Len = 100000;
    int num[Len], k = 0, new_num, a[Len], length;

    ifstream arr;
    arr.open("input.txt");

    if (!arr) {
        cout << "Unable to open file !"<<endl;
        return -1;
    }

    while (arr >> new_num) {
        a[k++] = new_num;
    }
    length = k;
	cout<<"Reading of array finished, "<<length<<" elements found."<<endl;


    cout<<"\n-------Sorting using InsertionSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    InsertionSort(num, length);
    End_time = clock();
    cout<<"The running time of InsertionSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));
    

    cout<<"\n-------Sorting using BubbleSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    BubbleSort(num, length);
    End_time = clock();
    cout<<"The running time of BubbleSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));
    

    cout<<"\n-------Sorting using SelectionSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    SelectionSort(num, length);
    End_time = clock();
    cout<<"Total running time SelectionSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));
    

    cout<<"\n-------Sorting using HeapSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    HeapSort(num, length);
    End_time = clock();
    cout<<"Total running time HeapSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));


    cout<<"\n-------Sorting using MergeSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    MergeSort(num, length);
    End_time = clock();
    cout<<"Total running time MergeSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));


    cout<<"\n-------Sorting using QuickSort-------"<<endl;
    for(int i = 0; i < length; i++){
        num[i] = a[i];
    }
    Start_time = clock();
    QuickSort(num, 0, length - 1);
    End_time = clock();
    cout<<"Total running time QuickSort is: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    cout<<"The first 20 elements are : ";
    print(num, min(20, length));

    return 0;
}
