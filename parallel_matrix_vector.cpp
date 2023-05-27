#include<iostream>
#include<omp.h>
using namespace std;
int main()
{
    cout<<endl;
    cout<<"Enter the number of elements in the vector: ";
    int nvec;
    cin>>nvec;

    int vec[nvec] = {0};

    for(int i=0; i<nvec; i++) vec[i] = rand()%10;
    cout<<endl;

    cout<<"Vector: ";
    for(int i=0; i<nvec; i++) cout<<vec[i]<<" ";
    cout<<endl;

    cout<<endl;
    cout<<"Enter the number of rows in the matrix: ";
    int rows;
    cin>>rows;

    int mat[rows][nvec];
    for(int i=0; i<rows; i++) for(int j=0; j<nvec; j++) mat[i][j] = rand()%10;
    cout<<endl;

    cout<<"Matrix: "<<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<nvec; j++) cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    cout<<"Multiplication: "<<endl;
    int rvec[rows];
    clock_t strt = clock();
    #pragma omp parallel for
    for(int i=0; i<rows; i++)
    {
        rvec[i] = 0;
        int arr[nvec] = {0};

        #pragma omp parallel for
        for(int j=0; j<nvec; j++) arr[j] = mat[i][j] * vec[j];

        int sum = 0;

        #pragma omp parallel for reduction(+: sum)
        for(int k = 0; k < nvec; k++) sum += arr[k];

        rvec[i] = sum;
    }
    clock_t stop = clock();


    for(int i=0; i<rows; i++) cout<<rvec[i]<<" ";
    cout<<endl;
    
    cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;
    
    return 0;
}

/*
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ g++ -fopenmp parallel_matrix_vector.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ ./a.out

Enter the number of elements in the vector: 3

Vector: 3 6 7 

Enter the number of rows in the matrix: 3

Matrix: 
5 3 5 
6 2 9 
1 2 7 

Multiplication: 
68 93 64 

Time required : 1403 ms
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ 

*/
