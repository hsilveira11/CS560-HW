//Name: Heather Silveira
//Student ID: t423f484
//Class: CS 560
//Programming Assignment
//Date Due: 4/25/18


#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ratio>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *A, int p, int r)
{
	int x = A[p]; //pivot is the first elem
	int i = p;
	int j = r;
	while (true)
	{
		while (!(A[i]>x || i>=j))
		{
			i++;
		}
		while (!(A[j]<x || j<i))
		{
			j--;
		}
		if (i<j)
		{
			swap (&A[i],&A[j]);
		}
		else
			break;
	}
	swap (&A[p],&A[j]);
	return j;
}

int randPartition(int *A, int p, int r)
{
	float d=rand()%999;
	d=d/1000;
	int index = p+ ((r-p+1)*d); //saving to int gives floor
	swap(&A[r],&A[index]);
	partition(A,p,r);
}

int quicksort(int *a, int m, int n)
{
    int index;
    if(m>=n)
        return 0;
    {
        index = partition(a,m,n);
        quicksort(a, m, index-1);
        quicksort(a, index+1, n);
    }
	return 0;
}
    
int randQuicksort(int *a, int m, int n)
{
    int index;
    if(m>=n)
        return 0;
    {
        index = randPartition(a,m,n);
        randQuicksort(a, m, index-1);
        randQuicksort(a, index+1, n);
    }
	return 0;
}


int main (void)
{
	
	int MAX_RANGE = 10000; 
	int N=0;
	int option=0;
	
	std::cout<< "Enter size of array" << "\n";
	std::cin >> N;
	int* myArr = new int[N];
	
	while (option != 1 && option!=2)
	{
		std::cout<< "Type 1 for random integers, or 2 for integers in increasing order: ";
		std::cin>> option;
	}
	
	
	std::ofstream myfile; //opening an output file
	myfile.open ("output.txt");
	myfile << "\nOriginal Values:\n ";
	std::cout<< "\nOriginal Values:\n";
	
	if (option==1)
	{
		srand((unsigned)time(0)); 
	    for(int i=0; i<N; i++)
		{ 
	        myArr[i] = (rand()%MAX_RANGE)+1; //random number
	        std::cout << myArr[i] << " ";
	        myfile << myArr[i]<< " "; //put array in output file
		}
	}
	if (option==2)
	{
		int X=0;
		std::cout<<"Please input a positive number to help create your increasing-order array: ";
		std::cin>>X;
		for(int i=0; i<N; i++)
		{ 
	        myArr[i] = N+(i+1)*X;
	        std::cout << myArr[i] << " ";
	        myfile << myArr[i]<< " "; //put array in output file
		}
		
	}
	
	
	//make copy array for Randomized quicksort to use
	int* myArr2 = new int[N];
	for(int i=0; i<N; i++)
	{ 
	    myArr2[i] = myArr[i];
	}
	
	
	myfile<<"\n\nQuicksort:\n ";
	std::cout<<"\n\nQuicksort:\n";
	auto start_time = std::chrono::high_resolution_clock::now(); //start timer
	quicksort(myArr,0,N-1);
	auto end_time = std::chrono::high_resolution_clock::now();//end timer


	//print
	for(int i=0; i<N; i++)
	{ 
        std::cout << myArr[i] << " ";
        myfile<< myArr[i] << " ";
	}
	
	//time
	std::chrono::duration<double, std::micro> x = end_time - start_time;
	std::cout <<"\nQuicksort Execution time: " << x.count() << " microseconds";
	myfile << "\nQuicksort Execution time: " << x.count() <<  " microseconds";
	
	
	
	
	myfile<<"\n\nRandomized Quicksort:\n ";
	std::cout<<"\n\nRandomized Quicksort:\n";
        auto start_time2 = std::chrono::high_resolution_clock::now(); //start timer
	randQuicksort(myArr2,0,N-1);
	auto end_time2 = std::chrono::high_resolution_clock::now();//end timer	
	

	//print
	for(int i=0; i<N; i++)
	{ 
        std::cout << myArr2[i] << " ";
        myfile<< myArr2[i] << " ";
	}
	
	//time
        std::chrono::duration<double, std::micro> y = end_time2 - start_time2;
        std::cout <<"\nRandomized Quicksort Execution time: " << y.count() << " microseconds";
        myfile << "\nRandomized Quicksort Execution time: " << y.count() << " microseconds";
	

	std::cout <<"\n\nTHE ABOVE RESULTS HAVE BEEN PRINTED TO output.txt";
	myfile.close();
	std::cout<<"\n";
	return 0;
	
	



}
