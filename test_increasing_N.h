
#ifndef TEST_INCREASING_N_H
#define TEST_INCREASING_N_H


#include "threads_compute.h"
#include "mmap_compute.h"
#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"
#include "commutative_functions.h"
#include <stdio.h>
#include <string.h>


void test_increasing_N(int lowerLim, int upperLim, int step, int parallelism, int argc, char *argv[], int filename_itr) {

    printf("Testing increasing N\n");

    //concatenate integer filename_itr to the filename
    char add_filename[100];
    char mul_filename[100];
    sprintf(add_filename, "test/increasing_N_add_%d.csv", filename_itr);
    sprintf(mul_filename, "test/increasing_N_mul_%d.csv", filename_itr);


    // printing headers and clearing files
    FILE *fp = fopen(add_filename, "w");
    fprintf(fp, "N,mmap,threads,sequential,parallel\n");
    fclose(fp);

    FILE *fp2 = fopen(mul_filename, "w");
    fprintf(fp2, "N,mmap,threads,sequential,parallel\n");
    fclose(fp2);

    for (int N = lowerLim; N <= upperLim; N += step)
    {
        generate_n("test/numbers.txt", N);

        printf("\033[1;36mIteration for N = %d\n\033[0m", N);

        unsigned long result = threads_compute(4, "test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Threads Result: %lu\n", result); }
  
        result = mmap_compute(4, "test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Mmap Result: %lu\n", result); }

        result = sequential_compute("test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Sequential Result: %lu\n", result); }

        result = parallel_compute("test/numbers.txt", 4, add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Parallel Result: %lu\n", result); }

        struct timespec startmmapAdd, endmmapAdd;
        struct timespec startthreadAdd, endthreadAdd;
        struct timespec startsequentialAdd, endsequentialAdd;
        struct timespec startparallelAdd, endparallelAdd;

        startmmapAdd = startmmap;
        endmmapAdd = endmmap;

        startthreadAdd = startthreads;
        endthreadAdd = endthreads;

        startsequentialAdd = startsequential;
        endsequentialAdd = endsequential;

        startparallelAdd = startparallel;
        endparallelAdd = endparallel;

        double mmapAddTime = (endmmapAdd.tv_sec - startmmapAdd.tv_sec) +  (endmmapAdd.tv_nsec - startmmapAdd.tv_nsec) / 1e9;
        double threadAddTime = (endthreadAdd.tv_sec - startthreadAdd.tv_sec) +  (endthreadAdd.tv_nsec - startthreadAdd.tv_nsec) / 1e9;
        double sequentialAddTime = (endsequentialAdd.tv_sec - startsequentialAdd.tv_sec) +  (endsequentialAdd.tv_nsec - startsequentialAdd.tv_nsec) / 1e9;
        double parallelAddTime = (endparallelAdd.tv_sec - startparallelAdd.tv_sec) +  (endparallelAdd.tv_nsec - startparallelAdd.tv_nsec) / 1e9;

        // print the time taken if verbose is enabled
        if (argc > 1 && strcmp(argv[1], "-v") == 0)
        {
            printf("Time taken for mmap add: %lf ns\n", mmapAddTime);
            printf("Time taken for threads add: %lf ns\n", threadAddTime);
            printf("Time taken for sequential add: %lf ns\n", sequentialAddTime);
            printf("Time taken for parallel add: %lf ns\n", parallelAddTime);
        }
       
        // write to csv file
        // clear buffer 
        FILE *fp = fopen(add_filename, "a");
        fflush(fp);
        fprintf(fp, "%d,%lf,%lf,%lf,%lf\n", N, mmapAddTime, threadAddTime, sequentialAddTime, parallelAddTime);
        fclose(fp);

        result = threads_compute(4, "test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("threads Result: %lu\n", result); }

        result = mmap_compute(4, "test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("mmap Result: %lu\n", result); }

        result = sequential_compute("test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Sequential Result: %lu\n", result); }

        result = parallel_compute("test/numbers.txt", 4, multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Parallel Result: %lu\n", result); }

        struct timespec startmmapMul, endmmapMul;
        struct timespec startthreadMul, endthreadMul;
        struct timespec startsequentialMul, endsequentialMul;
        struct timespec startparallelMul, endparallelMul;

        startmmapMul = startmmap;
        endmmapMul = endmmap;

        startthreadMul = startthreads;
        endthreadMul = endthreads;

        startsequentialMul = startsequential;
        endsequentialMul = endsequential;

        startparallelMul = startparallel;
        endparallelMul = endparallel;

        double mmapMulTime = (endmmapMul.tv_sec - startmmapMul.tv_sec) +  (endmmapMul.tv_nsec - startmmapMul.tv_nsec) / 1e9;
        double threadMulTime = (endthreadMul.tv_sec - startthreadMul.tv_sec) +  (endthreadMul.tv_nsec - startthreadMul.tv_nsec) / 1e9;
        double sequentialMulTime = (endsequentialMul.tv_sec - startsequentialMul.tv_sec) +  (endsequentialMul.tv_nsec - startsequentialMul.tv_nsec) / 1e9;
        double parallelMulTime = (endparallelMul.tv_sec - startparallelMul.tv_sec) +  (endparallelMul.tv_nsec - startparallelMul.tv_nsec) / 1e9;

        // print the time taken if verbose is enabled
        if (argc > 1 && strcmp(argv[1], "-v") == 0)
        {
            printf("Time taken for mmap multiply: %lf ns\n", mmapMulTime);
            printf("Time taken for threads multiply: %lf ns\n", threadMulTime);
            printf("Time taken for sequential multiply: %lf ns\n", sequentialMulTime);
            printf("Time taken for parallel multiply: %lf ns\n", parallelMulTime);
        }

        //write to csv file
        // clear buffer 
        FILE *fp2 = fopen(mul_filename, "a");
        fflush(fp2);
        fprintf(fp2, "%d,%lf,%lf,%lf,%lf\n", N, mmapMulTime, threadMulTime, sequentialMulTime, parallelMulTime);
        fclose(fp2);

        printf("\n");
    }


    return;
}



#endif
