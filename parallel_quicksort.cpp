#include<iostream>
#include<bits/stdc++.h>
#include<iomanip>
#include<omp.h>
using namespace std;

void quicksort(int arr[], int st, int end)
{
    if(st < end)
    {
        int pivot = arr[end];
        int i = st-1;
        int j = st;

        for(int var = j; var<end; var++)
        {
            if(arr[var] < pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[var];
                arr[var] = temp;
            }
        }

        // swap i+1 and end
        int temp = arr[i+1];
        arr[i+1] = arr[end];
        arr[end] = temp;

        i++;

        #pragma omp parallel sections
        {
            #pragma omp section
            quicksort(arr,st,i-1);

            #pragma omp section
            quicksort(arr,i+1,end);
        }
    
    }

}

int main()
{
    int n;
    cout<<"Enter the number of elements: "; 
    cin>>n;

    int arr[n] = {0};
    for(int i=0; i<n; i++) arr[i] = rand()%30;

    cout<<"Array: ";
    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    cout<<endl;

    clock_t strt = clock();
    quicksort(arr,0,n-1);
    clock_t stop = clock();

    cout<<"Sorted Array: ";
    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    
    
    cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;
    
    return 0;
}

/*
OUTPUT
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ g++ -fopenmp parallel_quicksort.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ ./a.out
Enter the number of elements: 10
Array: 13 16 27 25 23 25 16 12 9 1 
Sorted Array: 1 9 12 13 16 16 23 25 25 27 
Time required : 14842 ms
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ 

*/
