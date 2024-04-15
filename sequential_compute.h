#ifndef SEQUENTIAL_COMPUTE_H
#define SEQUENTIAL_COMPUTE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//File should contain comma seperated numbers

struct timespec startsequential, endsequential;

unsigned long sequential_compute(const char *filepath, unsigned long (*f)(unsigned long, unsigned long))
{
    FILE *file = fopen(filepath, "r");

    if (!file)
    {
        printf("Couldn't open file\n");
        exit(-1);
    }

    // start profiling
    clock_gettime(CLOCK_MONOTONIC, &startsequential);

    unsigned long result, temp;

    fscanf(file, "%ld", &result); 

    while (fscanf(file, ",%ld", &temp) == 1)
    { 
        result = f(result, temp);
    }

    fclose(file);

    // end profiling
    clock_gettime(CLOCK_MONOTONIC, &endsequential);

    return result;
}

#endif
