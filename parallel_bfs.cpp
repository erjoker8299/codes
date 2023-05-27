#include<iostream>
#include<vector>
#include<omp.h>
#include<queue>
#include<bits/stdc++.h>
using namespace std;

queue<int>q;

void bfs(int start, int* arr, int n, int visit[])
{
	#pragma omp parallel for ordered
	for(int i=0; i<n; i++)
	{
		#pragma omp ordered
		if( ( *(arr + (n*start) + i)  == 1 ) && (visit[i] == 0) )
		{
			cout<<i<<" ";
			q.push(i);
			visit[i] = 1;
		}
	}

	q.pop();

	if(!q.empty()) bfs(q.front(), (int*)arr, n, visit);
	
}

int main()
{
    cout<<"Enter the number of vertices: ";
    int n;
    cin>>n;

    int arr[n][n] = {0};

    cout<<"Enter the number of edges: ";
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

	int visit[n] = {0};

    cout<<"Enter the start vertex: ";
    int start;
    cin>>start;
	
	
	clock_t strt = clock();

	visit[start] = 1;
	cout<<start<<" ";
	q.push(start);

	bfs(start, (int*)arr, n, visit);

    clock_t stop = clock();

	cout<<"\nTime required : "<<(double)(stop-strt)<<" ms"<<endl;

    return 0;
}

/*
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ g++ -fopenmp parallel_bfs.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ ./a.out
Enter the number of vertices: 8
Enter the number of edges: 10
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
5 1 2 6 7 4 0 3 
Time required : 23770 ms
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/HPC$ 



*/
