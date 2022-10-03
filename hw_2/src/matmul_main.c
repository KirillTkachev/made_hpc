#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matmul_lib.h"

int main(int argc, char* argv[])
{
    int NRuns = 2;
    size_t i, j, k;
    
    if(argc != 2)
    {
    	printf("You should pass 1 argument");
    	return -1;
    } 
    
    char *matrix_size = argv[1];
    int N = atoi(matrix_size);
    printf("You have entered %d matrix size \n", N);
	
    double *runtimes;
    double *A, *B, *C;
    
    A = (double *) malloc(N * N * sizeof(double));
    B = (double *) malloc(N * N * sizeof(double));
    C = (double *) malloc(N * N * sizeof(double));
    runtimes = (double *) malloc(NRuns * sizeof(double));

    RandomMatrix(&A[0], N);
    RandomMatrix(&B[0], N);
    double average_runtime = 0.0;
// ijk ordering
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_ijk(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }

    printf("average runtime ijk %lf seconds\n", average_runtime);
    printf("---------------------------------\n");


// jik ordering
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_jik(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }

    printf("average runtime jik %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    

// kij ordering
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_kij(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime kij %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    
// kij ordering naive optimization (useless for -O3)
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_kij_opt(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime kij opt %lf seconds\n", average_runtime);
    printf("---------------------------------\n");

    free(A); 
    free(B);
    free(C);
    return 0;
}
