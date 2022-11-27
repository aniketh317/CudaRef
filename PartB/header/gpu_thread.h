// Create other necessary functions here
// __global__, __device__

//<<<Blocks per grid, Threads per block>>>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda.h"

__global__ void point_eval(int *A, int *B, int *C, int N)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int Nc = N>>1;
    int row = (index/Nc);//Division by a power of 2+Latency hiding
    int col = index-row*Nc;
    int sum = 0;
    int rA = row<<1;
    int cB = col<<1;
    for(int iter = 0; iter < N; iter++)
    {
        sum += A[rA * N + iter] * B[iter * N + cB];
        sum += A[rA * N + iter] * B[iter * N + cB + 1];
        sum += A[(rA + 1) * N + iter] * B[iter * N + cB];
        sum += A[(rA + 1) * N + iter] * B[iter * N + cB + 1];
    }
    C[index] = sum;
}

//Limit of number of threads per block is 128

// Fill in this function
void gpuThread(int N, int *matA, int *matB, int *output)
{
    int *dA, *dB, *dC;
    int nAB = N*N;
    int nC = (nAB)>>2;
    unsigned long num_bytesA = nAB*sizeof(int);
    unsigned long num_bytesB = nAB*sizeof(int);
    unsigned long num_bytesC = nC*(sizeof(int));

    cudaMalloc((void**)&dA, num_bytesA);
    cudaMalloc((void**)&dB, num_bytesB);
    cudaMalloc((void**)&dC, num_bytesC);
    
    cudaMemcpy(dA, matA, num_bytesA, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, matB, num_bytesB, cudaMemcpyHostToDevice);

    int threads_p_block = (512 < nC ? 512 : nC); //threads per block
    int num_blocks = nC/threads_p_block;

    point_eval<<<num_blocks, threads_p_block>>>(dA, dB, dC, N);
    cudaMemcpy(output, dC, num_bytesC, cudaMemcpyDeviceToHost);
    return;
}

