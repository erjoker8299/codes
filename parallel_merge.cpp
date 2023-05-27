#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
using namespace std;

void merge(int array[],int low1, int high1,int low2,int high2, int n)
{
	int temp[n];
	int i=low1,j=low2,k=0;
	
	while(i<=high1 && j<=high2)
	{
		if(array[i]<array[j])
			temp[k++]=array[i++];
		else
			temp[k++]=array[j++];
	}
	
	while(i<=high1)
		temp[k++]=array[i++];
	
	while(j<=high2) 
		temp[k++]=array[j++];
		
	for(i=low1,j=0;i<=high2;i++,j++)
		array[i]=temp[j];
}

void mergesort(int array[], int low, int high, int n)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(array,low,mid,n);
			}
			
			#pragma omp section
			{
				mergesort(array,mid+1,high,n);
			}
			
		}
		
        merge(array,low,mid,mid+1,high,n);


		// mergesort(array,low,mid,n);
		// mergesort(array,mid+1,high,n);
		// merge(array,low,mid,mid+1,high,n);
	}
}

void display(int array[], int n)
{
	for(int i=0;i<n;i++) cout<<array[i]<<" ";
}


int main()
{
	int n;
	cout<<"Enter the number of elements : ";
	cin>>n;
	
    int array[n] = {0};

	for(int i=0;i<n;i++)
	{
		array[i]=rand()%32;
	}
	
	cout<<"Original Array: ";
	display(array,n);
	cout<<endl;
	
	clock_t start = clock();
	mergesort(array,0,n-1,n);
	clock_t stop = clock();
	
	cout<<"Final Array: ";
	display(array,n);
	cout<<endl;

	cout<<"Time required : "<<(double)(stop-start)*1000/CLOCKS_PER_SEC<<" ms";
	
    return 0;
}

/*
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ g++ -fopenmp parallel_merge.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ ./a.out
Enter the number of elements : 10
Original Array: 7 6 9 19 17 31 10 12 9 13 
Final Array: 6 7 9 9 10 12 13 17 19 31 
Time required : 31.023 mskkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ 

*/
