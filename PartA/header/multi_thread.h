#include <pthread.h>
#include <iostream>
using namespace std;
// Create other necessary functions here

int N,N2,*matA,*matB,*output;

#define NUM_THREADS 8 //NUmber of threads possible in processor is 8

/*Change the order. Computation performed by single Thread piece*/
void *Tcomp(void *arg)
{
    int index = *((int*)arg);
    for(int rowA = index*N2; rowA < index*N2 + N2; rowA +=2) {
        int rowC = rowA>>1;
        for(int iter = 0; iter < N; iter++){
            for(int colB = 0; colB < N; colB+=2) 
            {
                int sum = 0;
                sum += matA[rowA * N + iter] * matB[iter * N + colB];
                sum += matA[(rowA+1) * N + iter] * matB[iter * N + colB];
                sum += matA[rowA * N + iter] * matB[iter * N + (colB+1)];
                sum += matA[(rowA+1) * N + iter] * matB[iter * N + (colB+1)];
        
                // compute output indices
                int colC = colB>>1;
                int indexC = rowC * (N>>1) + colC;
                output[indexC] += sum;
            }
    }
  }
  pthread_exit(NULL);
  return NULL;
}

// Fill in this function
void multiThread1(int Nl, int *matAl, int *matBl, int *outputl)
{
    N = Nl;
    matA = matAl;
    matB = matBl;
    output = outputl;
    assert( N>=4 and N == ( N &~ (N-1)));
    int k = NUM_THREADS;
    N2 = N;
    while(k>1){
        k >>= 1;
        N2 >>= 1;
    }
    int ind[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    for(int t=0; t<NUM_THREADS; t++){
        ind[t] = t;
        int iret = pthread_create( &threads[t], NULL, &Tcomp, (void*)(ind+t));
    }
    
    for(int t=0; t < NUM_THREADS; t++){
        (void) pthread_join(threads[t], NULL);
    }
}
