#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <stdio.h>
#include<omp.h>
#include<string.h>
#include<math.h>
#include<cstdlib>
#include<string.h>

using namespace std;

void insertintofile1(int n,int arr[])                                       //function for inserting numbers into file 1
{
ofstream out;
out.open("new1.txt",ios::out);
if(out.is_open())
	{
               for(int i=0;i<n;i++)
             {
               out<<arr[i]<<endl;
	      
             }
 out.close();
        }

}
void insertintofile2(int n,int arr[])                                 //function for inserting numbers in file 2
{ 
ofstream out;
out.open("new2.txt",ios::out);
if(out.is_open())
	{
               for(int i=0;i<n;i++)
             {
             
                   out<<arr[i]<<endl;
             }
        }
        out.close();

}

void add(int arr1[],int arr2[],int n1,int n2)                            //function for adding numbers from two files.
{
fstream out ,out1 ,out2;
int arr3[10000];
out2.open("output.txt",ios::out);                                           //open output file
out.open("new1.txt",ios::in);                                               //open first input file
out1.open("new2.txt",ios::in);                                              //open second input file
int sum=0;
int i=0,j=0,k=0;
if(out.is_open() && out1.is_open())
{

 while(i<n1||j<n2)
{

  out>>arr1[i];
  out1>>arr2[j];
//cout<<"arr1 "<<arr1[i]<<"\n";
//cout<<"arr2 "<<arr2[j]<<"\n";
  arr3[k]=arr1[i]+arr2[j];
//cout<<"arr3 "<<arr3[k]<<"\n";                                                           //write the result of addition into the third file.
   
  out2<<arr3[k];
  out2<<endl;
 i++,j++,k++;
  
}

}

}

void addparallel(int arr1[],int arr2[],int n1,int n2)                               //function to parallely fetch numbers from files and add.
{
fstream out ,out1 ,out2;
int arr3[10000];
out2.open("output2.txt",ios::out);
out.open("new1.txt",ios::in);
out1.open("new2.txt",ios::in);
int sum=0;
int i=0,j=0,k=0;
if(out.is_open() && out1.is_open())
{

#pragma omp parallel
while(i<n1 ||j<n2) 
{
out>>arr1[i];
out1>>arr2[j];


//cout<<"arr1 "<<arr1[i]<<"\n";
//cout<<"arr2 "<<arr2[j]<<"\n";

i++,j++ ;
}

i=0,j=0,k=0;
while(k<n1 ||k<n2)
{
            arr3[k]=arr1[i]+arr2[j];
        
           out2<<arr3[k]<<endl;
           i++,j++,k++;
   

}




}

 
}
int main()
{


int arr1[10000],arr2[10000];
int n1 ,n2;
cout<<"\nEnter the count of numbers in first file\n";
cin>>n1;
cout<<"Enter the numbers\n";
for(int i=0;i<n1;i++)
{
 arr1[i]=rand()%n1;
//cin>>arr1[i];

}
insertintofile1(n1,arr1);
cout<<"\nEnter the count of numbers in second  file\n";
cin>>n2;
cout<<"Enter the numbers\n";
double ts,tp;
for(int i=0;i<n2;i++)
{
 arr2[i]=rand()%n2;
//cin>>arr2[i];


}
double start,end;
insertintofile2(n2,arr2);
 start=omp_get_wtime();
add(arr1,arr2,n1,n2);
 end=omp_get_wtime();
cout<<"\nTime in sequential is "<<end-start;
ts=end-start;
 start=omp_get_wtime();
addparallel(arr1,arr2,n1,n2);
end=omp_get_wtime();
tp=end-start;
cout<<"\nTime in parallel is "<<end-start;

cout<<"\nSpeed up "<<ts/tp<<endl;
}
/*
g++ -fopenmp vectr.cpp

Enter the count of numbers in first file
10000
Enter the numbers

Enter the count of numbers in second  file
10000
Enter the numbers

Time in sequential is 0.0472238
Time in parallel is 0.0706983
Speed up 0.667961
*/