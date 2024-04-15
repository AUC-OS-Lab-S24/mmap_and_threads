#include "threads_compute.h"
#include "mmap_compute.h"
#include "parallel_compute.h"
#include "sequential_compute.h"
#include <stdio.h>
#include <string.h>
#include "generate_n.h"

unsigned long add(unsigned long a, unsigned long b)
{
    return a + b;
}

unsigned long multiply(unsigned long a, unsigned long b)
{
    return a * b;
}

int main(int argc, char *argv[])
{
    // generate numbers.txt file
    generate_n("test/numbers.txt", 10);

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

    // print the time taken if verbose is enabled

    if (argc > 1 && strcmp(argv[1], "-v") == 0)
    {
        printf("Time taken for mmap add: %lf ns\n", (endmmapAdd.tv_sec - startmmapAdd.tv_sec) +  (endmmapAdd.tv_nsec - startmmapAdd.tv_nsec) / 1e9);
        printf("Time taken for threads add: %lf ns\n", (endthreadAdd.tv_sec - startthreadAdd.tv_sec) +  (endthreadAdd.tv_nsec - startthreadAdd.tv_nsec) / 1e9);
        printf("Time taken for sequential add: %lf ns\n", (endsequentialAdd.tv_sec - startsequentialAdd.tv_sec) +  (endsequentialAdd.tv_nsec - startsequentialAdd.tv_nsec) / 1e9);
        printf("Time taken for parallel add: %lf ns\n", (endparallelAdd.tv_sec - startparallelAdd.tv_sec) +  (endparallelAdd.tv_nsec - startparallelAdd.tv_nsec) / 1e9);
    }


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

    // print the time taken if verbose is enabled
    if (argc > 1 && strcmp(argv[1], "-v") == 0)
    {
        printf("Time taken for mmap multiply: %lf ns\n", (endmmapMul.tv_sec - startmmapMul.tv_sec) +  (endmmapMul.tv_nsec - startmmapMul.tv_nsec) / 1e9);
        printf("Time taken for threads multiply: %lf ns\n", (endthreadMul.tv_sec - startthreadMul.tv_sec) +  (endthreadMul.tv_nsec - startthreadMul.tv_nsec) / 1e9);
        printf("Time taken for sequential multiply: %lf ns\n", (endsequentialMul.tv_sec - startsequentialMul.tv_sec) +  (endsequentialMul.tv_nsec - startsequentialMul.tv_nsec) / 1e9);
        printf("Time taken for parallel multiply: %lf ns\n", (endparallelMul.tv_sec - startparallelMul.tv_sec) +  (endparallelMul.tv_nsec - startparallelMul.tv_nsec) / 1e9);
    }

    return 0;
}

/*

For improvement:
This implementation is faster for reading files directly into memory, despite potential overhead from memory reallocation.
Used code: Essentially O(2n) due to reading the file twice—first to count the items and then to read them into an array. Simplified to O(n).
Second code: O(n) because it processes each item exactly once during the reading and storing operation.

 int *read_data(const char *filepath, int *size)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        printf("Failed to open fileeeee\n");
        return NULL;
    }

    int *data = NULL;
    *size = 0;
    int number;
    char delimiter;

    while (fscanf(file, "%d%c", &number, &delimiter) != EOF)
    {
        int *temp = realloc(data, sizeof(int) * (*size + 1));
        if (!temp)
        {
            printf("Failed to allocate memory\n");
            fclose(file);
            return NULL;
        }
        data = temp;
        data[*size] = number;
        (*size)++;

        if (delimiter != ',')
        {
            break;
        }
    }

    fclose(file);
    return data;
}



*/
