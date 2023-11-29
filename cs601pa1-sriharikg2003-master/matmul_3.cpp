#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pmmintrin.h>

// #include <pmmintrin.h>

#ifndef __SSE3__
#error This example requires SSE3
#endif

#include "timeutil.h"

/* Size of the matrices to multiply */
#define SIZE2 11
#define SIZE (1 << SIZE2)
// #define SIZE 2048

#define MINDEX(n, m) (((n) << SIZE2) | (m))

#define XMM_ALIGNMENT_BYTES 16 

static float *mat_a __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float *mat_b __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float *mat_c __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float *mat_d __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float *mat_ref __attribute__((aligned (XMM_ALIGNMENT_BYTES)));

static void
matmul_intrinsics()
{
        /* Assume that the data size is an even multiple of the 128 bit
         * SSE vectors (i.e. 4 floats) */
        assert(!(SIZE & 0x3));

        /* HINT: Read the documentation about the following. You might find at least the following instructions
         * useful:
         *  - _mm_setzero_ps
         *  - _mm_load_ps
         *  - _mm_hadd_ps
	 *  - _mm_mul_ps
         *  - _mm_cvtss_f32
         *
         * HINT: You can create the sum of all elements in a vector
         * using two hadd instructions.
         */

        /* Implement your SSE version of the matrix-vector
         * multiplication here.
         */
        for (int i = 0; i < SIZE; i++) {
                for(int j=0; j<SIZE;j++){
                        mat_d[i*SIZE+j] = mat_b[j*SIZE+i];
                }
        }

        for (int i = 0; i < SIZE; i++) {
                for(int k=0;k<SIZE;k++){
                        __m128 result = _mm_setzero_ps();
                        for (int j = 0; j < SIZE; j += 4) {
                                __m128 a = _mm_load_ps(&mat_a[MINDEX(i,j)]);
                                __m128 d = _mm_load_ps(&mat_d[MINDEX(k,j)]);
                                __m128 product = _mm_mul_ps(a, d);
                                result = _mm_add_ps(result, product);
                        }
                        result = _mm_hadd_ps(result, result);
                        result = _mm_hadd_ps(result, result);
                        float final_result = _mm_cvtss_f32(result);
                        mat_c[MINDEX(i,k)] = final_result;
                }
        }
}

/**
 * Reference implementation of the matvec used to verify the answer. Do NOT touch this function.
 */
static void
matvec_ref()
{
        int i, j, k;

	for (i = 0; i < SIZE; i++){
                for (j = 0; j < SIZE; j++){
                        for(k=0;k < SIZE; k++){
                                mat_ref[MINDEX(i,j)] += mat_a[MINDEX(i, k)] * mat_b[MINDEX(k,j)];
                        }
                }
        }
}

/**
 * Function used to verify the result. Do not touch this function.
 */
static int
verify_result()
{
        float e_sum;
        int i,j;
        int isPrecise = 0;
        int returnisPrecise=1;
        float max_diff;

        e_sum = 0;
        for (i = 0; i < SIZE; i++) {
                for (j=0; j<SIZE;j++){
                        isPrecise = mat_c[MINDEX(i,j)] - mat_ref[MINDEX(i,j)] < 1E-6;
                        max_diff = max_diff < mat_c[MINDEX(i,j)] - mat_ref[MINDEX(i,j)] ? mat_c[MINDEX(i,j)] - mat_ref[MINDEX(i,j)] : max_diff ;
                        if (!isPrecise){
                                returnisPrecise = 0;
                                printf("max_difference: %.e\n", max_diff);
                                return returnisPrecise;
                        }
                }
        }

        // returnisPrecise = 1;

        printf("max_difference: %.e\n", max_diff);
        return returnisPrecise;
}

/**
 * Initialize mat_a and vec_b with "random" data. Write to every
 * element in mat_c to make sure that the kernel allocates physical
 * memory to every page in the matrix before we start doing
 * benchmarking.
 */
static void
init()
{
        int i, j;

        mat_a = (float *)_mm_malloc(sizeof(*mat_a) * SIZE * SIZE, XMM_ALIGNMENT_BYTES);
        mat_b = (float *)_mm_malloc(sizeof(*mat_b) * SIZE *SIZE, XMM_ALIGNMENT_BYTES);
        mat_c = (float *)_mm_malloc(sizeof(*mat_c) * SIZE *SIZE, XMM_ALIGNMENT_BYTES);
        mat_d = (float *)_mm_malloc(sizeof(*mat_c) * SIZE *SIZE, XMM_ALIGNMENT_BYTES);
        mat_ref = (float *)_mm_malloc(sizeof(*mat_ref) * SIZE * SIZE, XMM_ALIGNMENT_BYTES);

        if (!mat_a || !mat_b || !mat_c  || !mat_d  || !mat_ref) {
                fprintf(stderr, "Memory allocation failed\n");
                abort();
        }

        for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++){
                        mat_a[MINDEX(i, j)] = ((7 * i + j) & 0x0F) * 0x1P-2F;
                        mat_b[MINDEX(i, j)] = ((7 * i + j) & 0x0F) * 0x1P-2F;
                }
        }

        memset(mat_c, 0, sizeof(mat_c));
        memset(mat_d, 0, sizeof(mat_d));
        memset(mat_ref, 0, sizeof(mat_ref));
}

static void
run_multiply()
{
        struct timespec ts_start, ts_stop;
        double runtime_ref, runtime_sse;

        get_time_now(&ts_start);
        /* vec_c = mat_a * vec_b */
        matmul_intrinsics();
        get_time_now(&ts_stop);
        runtime_sse = get_time_diff(&ts_start, &ts_stop);
        printf("Matvec using intrinsics completed in %.2f s\n",
               runtime_sse);

        get_time_now(&ts_start);
	    matvec_ref();
        get_time_now(&ts_stop);
        runtime_ref = get_time_diff(&ts_start, &ts_stop);
        printf("Matvec reference code completed in %.2f s\n",
               runtime_ref);

        printf("Speedup: %.2f\n",
               runtime_ref / runtime_sse);


	if (verify_result())
	    printf("Result OK\n");
	else
	    printf("Result MISMATCH\n");
}

int
main(int argc, char *argv[])
{
        /* Initialize the matrices with some "random" data. */
        init();

        run_multiply();

        _mm_free(mat_a);
        _mm_free(mat_b);
        _mm_free(mat_c);
        _mm_free(mat_ref);

        return 0;
}
