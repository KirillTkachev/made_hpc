#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    const size_t N = 100;
    const size_t chunk = 3;

    int i, tid;
    float a[N], b[N], c[N];

    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (float)i;
    }

    for (i = 0; i < N; ++i)
    {
        c[i] = a[i] + b[i];
        printf("c[%d] = %f\n", i, c[i]);
    } 
    return 0;
}
