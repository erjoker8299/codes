#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void dfs(int start, int* arr, int n, int visited[]) {

    //#pragma omp parallel for ordered
    for(int i = 0; i < n; i++) {
        //#pragma omp ordered
        if( (*(arr + (start*n) + i) == 1) && (!visited[i]) )
        {
            visited[i] = 1;
            cout<<i<<" ";
            dfs(i, (int*)arr, n, visited);
        }
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

	cout<<"Enter the number of vertices:";
    int n;
    cin>>n;
	
    int arr[n][n] = {0};

    cout<<"Enter the number of edges:";
    int edges;
    cin>>edges;
    

    for(int j=0; j<edges; j++)
    {
        int a, b;
        cout<<"Enter the two edges:"<<endl;
        cin>>a>>b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    int visited[n] = {0};

    cout<<"Enter the start vertex: ";
    int start;
    cin>>start;

    clock_t strt = clock();
    
    cout<<start<<" ";
    visited[start] = 1;
	dfs(start, (int *)arr, n, visited);
    
    clock_t stop = clock();

    cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;


    return 0;
}


/*

kw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ g++ -fopenmp parallel_dfs.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ ./a.out
Enter the number of vertices:8
Enter the number of edges:10
Enter the two edges:
0 3
Enter the two edges:
4 0
Enter the two edges:
5 1
Enter the two edges:
5 2
Enter the two edges:
5 6
Enter the two edges:
5 7
Enter the two edges:
6 2
Enter the two edges:
2 4
Enter the two edges:
4 7
Enter the two edges:
6 7
Enter the start vertex: 5
5 1 2 4 0 3 7 6 
Time required : 17 ms


*/
