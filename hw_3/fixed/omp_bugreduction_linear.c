#include <stdio.h>
#include <stdlib.h>

float dotprod(float * a, float * b, size_t N)
{
    int i;
    float sum = 0.0;

    for (i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
        printf("i = %d\n", i);
    }

    return sum;
}

int main (int argc, char *argv[])
{
    const size_t N = 100;
    int i;
    float sum;
    float a[N], b[N];


    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double) i;
    }

    sum = 0.0;

    sum = dotprod(a, b, N);

    printf("Sum = %f\n",sum);

    return 0;
}
