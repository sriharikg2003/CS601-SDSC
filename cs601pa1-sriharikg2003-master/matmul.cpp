// //CS601: example code to show how matrix multiplication code
// //shows orders of magnitude of performance difference when
// //using -O3, loop interchange, and parallelization optimizations.

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<immintrin.h>

#ifdef CBLAS
#include "cblas.h"
#endif


const int INPUTSIZE = 2048; 
// A and B are inputs and C is the output. R is the reference matrix used for verification.
float* A=new float[INPUTSIZE*INPUTSIZE];
float* B=new float[INPUTSIZE*INPUTSIZE];
float* C=new float[INPUTSIZE*INPUTSIZE];
float* R=new float[INPUTSIZE*INPUTSIZE];

// Verification Code 
static void verify(){
    int n = INPUTSIZE;
    std::cout << "inside" << std::endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){

            R[i*n+j]=0;
        }  
    }

// IKJ REFERENCE MATRIX for Verification Code
    for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                R[i*n+j] = R[i*n+j] + A[i*n+k] * B[k*n+j];

    float e_sum, max_err;
    // e_sum is the error in values of current cell; max_err is the maximum error till any instant
    e_sum = 0;
    max_err = 0;
   
    for(int i=0; i<INPUTSIZE ; i++){
        for(int j=0; j<INPUTSIZE; j++){

        e_sum = C[i*n+j] < R[i*n+j] ?
                        R[i*n+j] - C[i*n+j] :
                        C[i*n+j] - R[i*n+j];
        if (e_sum>max_err){ // update max error if current error is greater than max error till the given instant
            max_err = e_sum;
            }
        }
    }
    std::cout << "max_err: " << max_err << std::endl;
    if (max_err< 0.002){
        std::cout << "verfied" << std::endl;
    }
    return;
}

int main(int argc, char* argv[]){
    int c=0;
    int n = INPUTSIZE;
  

    std::srand(std::time(NULL));
    #ifdef STACKALLOCATED
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i][j] = std::rand() / (float)(RAND_MAX);
            B[i][j] = std::rand() / (float)(RAND_MAX);
            C[i][j]=0;
        }  
    }
    // initializing A and B. Also initializing C to 0s.
    #else    
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                A[i*n+j] = std::rand() / (float)(RAND_MAX);
                B[i*n+j] = std::rand() / (float)(RAND_MAX);
                C[i*n+j]=0;
            }  
        }
    #endif

    const auto start=std::chrono::steady_clock::now();

#ifdef STACKALLOCATED
for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
#endif

#ifdef PARALLEL
#pragma omp parallel for
#endif 

#ifdef IJK_LOOP // for ijk loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds ijk: " << elapsedtimes.count() << std::endl;       
#endif

#ifdef IKJ_LOOP // for ikj loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds ikj: " << elapsedtimes.count() << std::endl;  
#endif

#ifdef JIK_LOOP // for jik loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int j=0;j<n;j++)
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds jik: " << elapsedtimes.count() << std::endl;       
#endif

#ifdef JKI_LOOP // for jki loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int j=0;j<n;j++)
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds jki: " << elapsedtimes.count() << std::endl;       
#endif

#ifdef KIJ_LOOP // for kij loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];

       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds kij: " << elapsedtimes.count() << std::endl;       
#endif

#ifdef KJI_LOOP // for kji loop
    c=1;
    const auto start2 = std::chrono::steady_clock::now();
    for(int k=0;k<n;k++)
        for(int j=0;j<n;j++)
            for(int i=0;i<n;i++)
                C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
       const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds kji: " << elapsedtimes.count() << std::endl;       
#endif

#ifdef SGEMM // for question 1 part c. Using SGEMM function for matrix multiplication using CBLAS
    // initilizing A and B and also result matrix C to 0.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = std::rand() / (float)(RAND_MAX);
            B[i * n + j] = std::rand() / (float)(RAND_MAX);
            C[i * n + j] = 0;
        }
    }

    const auto start2 = std::chrono::steady_clock::now();
    // the function that executes matrx multiplication
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 1.0, C, n);

    const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds sgemm: " << elapsedtimes.count() << std::endl;
    c=1;
#endif


#ifdef SDOT // for the dot product part of question 1 part c

    float** P = new float*[INPUTSIZE];

    // Allocate memory for each row
    for(int x = 0; x < INPUTSIZE; ++x) {
        P[x] = new float[INPUTSIZE];
    }

    float** Q = new float*[INPUTSIZE];

    // Allocate memory for each row
    for(int x = 0; x < INPUTSIZE; ++x) {
        Q[x] = new float[INPUTSIZE];
    }
    // initializing P and Q as 2D matrices
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            P[i][j] = std::rand() / (float)(RAND_MAX);
            Q[i][j] = std::rand() / (float)(RAND_MAX);
        }  
    }

    float* I=new float[INPUTSIZE*INPUTSIZE];
    float* D=new float[n*n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = std::rand() / (float)(RAND_MAX);
            B[i * n + j] = std::rand() / (float)(RAND_MAX);
            C[i * n + j] = 0;
            D[i*n+j] = 0;
            I[i*n+j] = 0;
            if(i==j) {
                 I[i*n+j] = 1;
            }
        }
    }
    // for taking transpose of second matrix
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, n, 1.0, B, n, I, n, 1.0, D, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            P[i][j] = A[i*n+j];
            Q[i][j] = D[i*n+j];
        }
    }

    const auto start2 = std::chrono::steady_clock::now();
    // dot product
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){ 
        C[i*n+j]=cblas_sdot(n , P[i] , 1  , Q[j] , 1);
        }
    }
    const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds sdot: " << elapsedtimes.count() << std::endl;
 
    c=1;
#endif

    verify();
    std::cout << "verified";    
    delete[] A;
    delete[] B;
    delete[] C;

}