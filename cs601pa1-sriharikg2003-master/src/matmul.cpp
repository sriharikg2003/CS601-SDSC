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


// IKJ REFERENCE MATRIX


    for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                R[i*n+j] = R[i*n+j] + A[i*n+k] * B[k*n+j];





    float e_sum, max_err;

    e_sum = 0;
    max_err = 0;
   
    for(int i=0; i<INPUTSIZE ; i++){
        for(int j=0; j<INPUTSIZE; j++){

        e_sum = C[i*n+j] < R[i*n+j] ?
                        R[i*n+j] - C[i*n+j] :
                        C[i*n+j] - R[i*n+j];
        if (e_sum>max_err){
            max_err = e_sum;
            }
        }
    }

        std::cout << "max_err: " << max_err << std::endl;
std::cout << "verfied" << std::endl;

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

#else    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i*n+j] = std::rand() / (float)(RAND_MAX);
            B[i*n+j] = std::rand() / (float)(RAND_MAX);
            C[i*n+j]=0;
        }  
    }
#endif
//   A[0]=1;
//     A[1]=2;
//     A[2]=3;
//     A[3]=4;

//     B[0]=10;
//     B[1]=20;
//     B[2]=30;
//     B[3]=40;
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

#ifdef IJK_LOOP
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


#ifdef IKJ_LOOP
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
#ifdef JIK_LOOP
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
#ifdef JKI_LOOP
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

#ifdef KIJ_LOOP
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

#ifdef KJI_LOOP
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



#ifdef SGEMM
 
  
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = std::rand() / (float)(RAND_MAX);
            B[i * n + j] = std::rand() / (float)(RAND_MAX);
            C[i * n + j] = 0;
        }
    }

    const auto start2 = std::chrono::steady_clock::now();

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 1.0, C, n);

    const auto end2 = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedtimes = end2 - start2;
    std::cout << "elapsed seconds sgemm: " << elapsedtimes.count() << std::endl;

 

    c=1;
#endif


#ifdef SDOT

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



    
    // cblas_strsm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, n, n, 1.0, B, n, D, n);
// cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 1.0, C, n);

    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, n, 1.0, B, n, I, n, 1.0, D, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            P[i][j] = A[i*n+j];
            Q[i][j] = D[i*n+j];
        }
    }

    const auto start2 = std::chrono::steady_clock::now();
    // float v1[n], v2[n];
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
