#include<iostream>
#include<omp.h>
#include<time.h>
#define N 1000
using namespace std;
int mat1[N][N];
int mat2[N][N];
int mat3[N][N];

void parallelmultiplication(int mat1[N][N],int mat2[N][N],int mat3[N][N])
{
    int i,j,k;
    #pragma omp parallel for private(i,j,k) shared(mat1,mat2,mat3)
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
void serialmultiplication(int mat1[N][N],int mat2[N][N],int mat3[N][N])
{
    int i,j,k;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main()
{
    int i,j,k;
    float ts=0,tp=0,starts,ends,startp,endp;



    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            mat1[i][j] = 2;
            mat2[i][j] = 3;
        }
    }

    startp = omp_get_wtime();
    parallelmultiplication(mat1,mat2,mat3);
    endp = omp_get_wtime();

    starts = omp_get_wtime();
    serialmultiplication(mat1,mat2,mat3);
    ends = omp_get_wtime();

    tp = endp-startp;
    cout<<"tp = "<<tp<<endl;

    ts = ends-starts;
    cout<<"ts = "<<ts<<endl;

    cout<<"Speed up = "<<ts/tp<<endl;
    return 0;

}