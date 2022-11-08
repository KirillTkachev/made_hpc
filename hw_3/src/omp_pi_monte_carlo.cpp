#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include <time.h>        
#include <cmath>
#include <limits.h>

#include <chrono>


const int nThreads = 4;
unsigned int seeds[nThreads];

void seedThreads() {
    int my_thread_id;
    unsigned int seed;
    #pragma omp parallel private (seed, my_thread_id)
    {
        my_thread_id = omp_get_thread_num();
        
        //create seed on thread using current time
        unsigned int seed = (unsigned) time(NULL);
        
        //munge the seed using our thread number so that each thread has its
        //own unique seed, therefore ensuring it will generate a different set of numbers
        seeds[my_thread_id] = (seed & 0xFFFFFFF0) | (my_thread_id + 1);
        
        printf("Thread %d has seed %u\n", my_thread_id, seeds[my_thread_id]);
    }
    
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
    	printf("You should pass 1 argument");
    	return -1;
    }
    
    char *size = argv[1];
    const long N = atol(size); 
	
    long flips = 0;
    
    omp_set_num_threads(nThreads);  
    seedThreads(); 
    
    long hits = 0;
    double pi;
    
    int tid;       
    unsigned int seed;
    double start = 0.0;
    double end = 0.0;
    start = omp_get_wtime(); 
    #pragma omp parallel num_threads(nThreads) default(none) \
        private(flips, tid, seed) \
        shared(N, seeds) \
        reduction(+:hits)
    {
        tid = omp_get_thread_num();   
        seed = seeds[tid];            
	srand(seed);	    
		
	double x = 0.0;
	double y = 0.0;
		          
        #pragma omp for
        for (flips = 0; flips < N; flips++) 
        {
            x = (rand_r(&seed) / (double) RAND_MAX);
            y = (rand_r(&seed) / (double) RAND_MAX);
            
            if (sqrt(x * x + y * y) <= 1) 
            {
                hits += 1;
            }
        }
    }
    end = omp_get_wtime(); 
    
    pi = ((double) hits * 4.0 / (double) N);

    printf("pi = %1.10f \n", pi);
    printf("elapsed time = %1.10f \n", end - start);

    return 0;
}
