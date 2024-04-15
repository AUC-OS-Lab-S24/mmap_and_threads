#ifndef  TEST_INCREASING_PARALLELISM_H 
#define TEST_INCREASING_PARALLELISM_H

#include "threads_compute.h"
#include "mmap_compute.h"
#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"
#include "commutative_functions.h"
#include <stdio.h>
#include <string.h>

void test_increasing_parallelism(int upperLim, int fixed_N, int argc, char *argv[], int filename_itr) {

    printf("Testing increasing parallelism\n");
    
    char add_filename[100];
    char mul_filename[100];
    sprintf(add_filename, "test/increasing_parallelis_add_%d.csv", filename_itr);
    sprintf(mul_filename, "test/increasing_parallelis_mul_%d.csv", filename_itr);

    // printing headers and clearing files
    FILE *fp = fopen(add_filename, "w");
    fprintf(fp, "Parallelism,mmap,threads,sequential,parallel\n");
    fclose(fp);

    FILE *fp2 = fopen(mul_filename, "w");
    fprintf(fp2, "Parallelism,mmap,threads,sequential,parallel\n");
    fclose(fp2);

    generate_n("test/numbers.txt", fixed_N);

    for (int i = 1; i <= upperLim; i++)
    {

        printf("\033[1;36mIteration for parallelism = %d\n\033[0m", i);

        unsigned long result = threads_compute(i, "test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Threads Result: %lu\n", result); }

        result = mmap_compute(i, "test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Mmap Result: %lu\n", result); }

        result = sequential_compute("test/numbers.txt", add);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Sequential Result: %lu\n", result); }

        result = parallel_compute("test/numbers.txt", i, add);
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
        fprintf(fp, "%d,%lf,%lf,%lf,%lf\n", i, mmapAddTime, threadAddTime, sequentialAddTime, parallelAddTime);
        fclose(fp);

        result = threads_compute(i, "test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Threads Result: %lu\n", result); }

        result = mmap_compute(i, "test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Mmap Result: %lu\n", result); }

        result = sequential_compute("test/numbers.txt", multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Sequential Result: %lu\n", result); }

        result = parallel_compute("test/numbers.txt", i, multiply);
        if (argc > 1 && strcmp(argv[1], "-v") == 0) { printf("Parallel Result: %lu\n", result); }

        struct timespec startmmapMultiply, endmmapMultiply;
        struct timespec startthreadMultiply, endthreadMultiply;
        struct timespec startsequentialMultiply, endsequentialMultiply;
        struct timespec startparallelMultiply, endparallelMultiply;

        startmmapMultiply = startmmap;
        endmmapMultiply = endmmap;

        startthreadMultiply = startthreads;
        endthreadMultiply = endthreads;

        startsequentialMultiply = startsequential;
        endsequentialMultiply = endsequential;

        startparallelMultiply = startparallel;
        endparallelMultiply = endparallel;


        double mmapMultiplyTime = (endmmapMultiply.tv_sec - startmmapMultiply.tv_sec) +  (endmmapMultiply.tv_nsec - startmmapMultiply.tv_nsec) / 1e9;
        double threadMultiplyTime = (endthreadMultiply.tv_sec - startthreadMultiply.tv_sec) +  (endthreadMultiply.tv_nsec - startthreadMultiply.tv_nsec) / 1e9;
        double sequentialMultiplyTime = (endsequentialMultiply.tv_sec - startsequentialMultiply.tv_sec) +  (endsequentialMultiply.tv_nsec - startsequentialMultiply.tv_nsec) / 1e9;
        double parallelMultiplyTime = (endparallelMultiply.tv_sec - startparallelMultiply.tv_sec) +  (endparallelMultiply.tv_nsec - startparallelMultiply.tv_nsec) / 1e9;

        // print the time taken if verbose is enabled
        if (argc > 1 && strcmp(argv[1], "-v") == 0)
        {
            printf("Time taken for mmap multiply: %lf ns\n", mmapMultiplyTime);
            printf("Time taken for threads multiply: %lf ns\n", threadMultiplyTime);
            printf("Time taken for sequential multiply: %lf ns\n", sequentialMultiplyTime);
            printf("Time taken for parallel multiply: %lf ns\n", parallelMultiplyTime);
        }

        // write to csv file
        FILE *fp2 = fopen(mul_filename, "a");
        fflush(fp2);
        fprintf(fp2, "%d,%lf,%lf,%lf,%lf\n", i, mmapMultiplyTime, threadMultiplyTime, sequentialMultiplyTime, parallelMultiplyTime);
        fclose(fp2);

    }

    return;
}

#endif
