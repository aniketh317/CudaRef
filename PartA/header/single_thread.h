// Optimize this function

void singleThread(int N, int *matA, int *matB, int *output)
{
  assert( N>=4 and N == ( N &~ (N-1)));
  for(int rowA = 0; rowA < N; rowA +=2) {
    for(int colB = 0; colB < N; colB += 2){
      int sum = 0;
      for(int iter = 0; iter < N; iter++) 
      {
        sum += matA[rowA * N + iter] * matB[iter * N + colB];
        sum += matA[(rowA+1) * N + iter] * matB[iter * N + colB];
        sum += matA[rowA * N + iter] * matB[iter * N + (colB+1)];
        sum += matA[(rowA+1) * N + iter] * matB[iter * N + (colB+1)];
      }

      // compute output indices
      int rowC = rowA>>1;
      int colC = colB>>1;
      int indexC = rowC * (N>>1) + colC;
      output[indexC] = sum;
    }
  }
}

/*Change the order*/
void singleThread2(int N, int *matA, int *matB, int *output)
{
  assert( N>=4 and N == ( N &~ (N-1)));
  for(int rowA = 0; rowA < N; rowA +=2) {
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
}

/*Loop-Tiling based*/
void singleThread3(int N, int *matA, int *matB, int *output, int T=2)
{
  assert( N>=4 and N == ( N &~ (N-1)));
  for(int rowA = 0; rowA < N; rowA +=T) {
    for(int iter = 0; iter < N; iter += T){
      for(int colB = 0; colB < N; colB += T){
        for(int rr = rowA; rr < rowA + T; rr += 2){
          int rowC = rr >> 1;
          for(int ii = iter; ii < iter + T; ii ++){
            for(int cc = colB; cc < colB + T; cc += 2)
            {
              int sum = 0;
              sum += matA[rr * N + ii] * matB[ii * N + cc];
              sum += matA[(rr+1)*N + ii] * matB[ii * N + cc];
              sum += matA[rr * N + ii] * matB[ii * N + (cc + 1)];
              sum += matA[(rr + 1) * N + ii] * matB[ii * N + (cc + 1)];

              // compute output indices
              int colC = cc>>1;
              int indexC = rowC * (N>>1) + colC;
              output[indexC] += sum;
            }
          }
        }
      } 
    }
  }
}