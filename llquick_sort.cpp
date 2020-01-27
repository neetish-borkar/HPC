#include<iostream>
#include<cstdlib>
#include<omp.h>
using namespace std;

long int partition(long int arr[],long int low,long int high){
    long int pivot=arr[high];
    long int temp;
    long int i = low-1;
    for (long int j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
        }
    }
    i++;
    temp=arr[i];
    arr[i]=arr[high];
    arr[high]=temp;
    return i;
}


long int quick_sort_ll(long int arr[],long int low,long int high){
    if(low<high){
        long int mid = partition(arr,low,high);
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quick_sort_ll(arr,low,mid-1);
            }
            #pragma omp section
            {
            quick_sort_ll(arr,mid+1,high);
            }
        }

    }
}
long int quick_sort(long int arr[],long int low,long int high){
    if(low<high){
        long int mid = partition(arr,low,high);
        quick_sort(arr,low,mid-1);
        quick_sort(arr,mid+1,high);
    }
}

int main(){
    long int n;
    cout<<"Enter the number of elements:"<<endl;
    cin>>n;

    long int arr[n];
    cout<<"Inserting elements"<<endl;
    for(long int i=0;i<n;i++){
        arr[i]=(rand()%1000000);
    }
    cout<<"Insertion completed"<<endl;
    cout<<"Sorting elements with parallel Quick Sort"<<endl;
    double starttime;
    starttime = omp_get_wtime();
    quick_sort_ll(arr,0,n-1);
    double endtime = omp_get_wtime();
    cout<<"Parallel Quick Sorting completed"<<endl;

    cout<<"Sorting elements with Serial Quick Sort"<<endl;
    double starttime2;
    starttime2 = omp_get_wtime();
    quick_sort(arr,0,n-1);
    double endtime2 = omp_get_wtime();
    cout<<"Serial Quick Sorting completed"<<endl;
    double ts=(endtime2 - starttime2);
    double tp=(endtime - starttime);
    cout << "Time Parallel: " << tp<<endl;
    cout << "Time serial: " << ts<<endl;
    cout<<"Speed up: "<<ts/tp<<endl;

    return 0;
}
/*
g++ -fopenmp llquick_sort.cpp
Enter the number of elements:
12000
Inserting elements
Insertion completed
Sorting elements with parallel Quick Sort
Parallel Quick Sorting completed
Sorting elements with Serial Quick Sort
Serial Quick Sorting completed
Time Parallel: 0.0236454
Time serial: 0.27207
Speed up: 11.5062
*/
