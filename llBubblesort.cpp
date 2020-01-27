#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <time.h>
using namespace std;

class sort{

public:
    int *array;
    int  size;
    int *array2;
    void accept(int);
    void display();
    void display2();
    void bubb_sort_ll();
    void bubble_sort();
    void check();

};
void sort::accept(int s){
    size=s;
    array=new int [size];
    array2=new int [size];
    for (int i=0;i<size;i++){
        int x=rand()%size;
        array[i]=x;
        array2[i]=x;
        
    }
}

void sort::check(){
    for(int i=0;i<size;i++){
        if(array[i]!=array2[i]){
            cout<<"worng"<<endl;
            break;
        }
    }
}

void sort::display(){
    for(int i=0; i<size;i++)
    {
        cout<<array[i]<<endl;
    }
}

void sort::display2(){
    for(int i=0; i<size;i++)
    {
        cout<<array2[i]<<endl;
    }
}

void sort::bubb_sort_ll(){
    int temp;

	for (int i = 0; i < size/2; i++)
	{
		#pragma omp parallel for private(temp)  
		for (int j = 0; j < size-1; j+=2) 
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
		#pragma omp parallel for private(temp)  
		for (int j = 1; j < size-1; j+=2) 
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}	
	}
}
void sort::bubble_sort(){
    int temp;

    for(int i=0;i<size-1;i++){

        for(int j=0;j<size-i-1;j++){
        
            if(array2[j]>array2[j+1]){
                temp=array2[j];
				array2[j]=array2[j+1];
				array2[j+1]=temp;
            }
        }
    }

}


int main(){
    int s;
    double wtime;
    double wtime2;
    cout<<"Enter the length of array"<<endl;
    cin>>s;
    sort a;


    wtime=omp_get_wtime();
    a.accept(s);    
    cout<<"Initialized Array"<<endl;
    //a.display();
    wtime2=omp_get_wtime()-wtime;


    double wtime3=omp_get_wtime();
    cout<<"Prallel Sorted Array"<<endl;
    a.bubb_sort_ll();
    //a.display();
    double wtime4=omp_get_wtime()-wtime3;


    double wtime5=omp_get_wtime();
    cout<<"Normal Sorted Array"<<endl;
    a.bubble_sort();
    //a.display2();
    double wtime6=omp_get_wtime()-wtime5;

    a.check();

    cout<<"Size="<<a.size<<endl;
    cout<<"Time taken to initialize Array= "<<wtime2<<"s"<<endl;
    cout<<"Time taken to Prallel Bubble Sort Array= "<<wtime4<<"s"<<endl;
    cout<<"Time taken to Bubble Sort Array= "<<wtime6<<"s"<<endl;
    cout<<"Speed up= "<<wtime6/wtime4<<endl;
}
/*
g++ -fopenmp llBubblesort.cpp
Enter the length of array
10000
Initialized Array
Prallel Sorted Array
Normal Sorted Array
Size=10000
Time taken to initialize Array= 0.000657213s
Time taken to Prallel Bubble Sort Array= 0.193904s
Time taken to Bubble Sort Array= 0.469301s
Speed up= 2.42027
*/