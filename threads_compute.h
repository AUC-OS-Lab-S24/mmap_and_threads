#ifndef THREADS_COMPUTE_H
#define THREADS_COMPUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// For Profiling we have global variable here for clock time
struct timespec startthreads, endthreads;

/*
 * Takes the number of threads, a path to a file containing numbers, a pointer to a function that takes 2 integers and returns an unsigned long integer.
 * Returns the result of applying the function on the numbers as an unsigned long integer by splitting the work as evenly as possible using multiple processes working together via shared memory.
 */

// int pthread_create (pthread_t * thread, const pthread_attr_t * attr, void * (*start_routine)(void *), void *arg);
// attr will be NULL
// arg will be a struct containing the array of numbers, start index, end index and the function pointer

struct thread_args
{
    unsigned long *numbers;
    unsigned long start;
    unsigned long end;
    unsigned long (*func)(unsigned long, unsigned long);
};

void *compute(void *arg)
{
    struct thread_args *args = (struct thread_args *)arg;
    unsigned long *numbers = args->numbers;
    unsigned long start = args->start;
    unsigned long end = args->end;
    unsigned long (*func)(unsigned long, unsigned long) = args->func;

    unsigned long result = numbers[start];
    for (int i = start + 1; i < end; i++)
    {
        result = func(result, numbers[i]);
    }

    return (void *)result;
}

unsigned long threads_compute(int num_threads, char *path, unsigned long (*func)(unsigned long, unsigned long))
{
    // Open the file
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // get the number of integers in the file
    int temp, count = 1;
    fscanf(file, "%d", &temp);

    while (fscanf(file, ",%d", &temp) == 1)
    {
        count++;
    }
    // move file pointer to start
    fseek(file, 0, SEEK_SET);

    // Read the integers into an array
    unsigned long *numbers = (unsigned long *)malloc(count * sizeof(unsigned long));
    fscanf(file, "%lu", &numbers[0]);
    for (int i = 1; i < count; i++)
    {
        fscanf(file, ",%lu", &numbers[i]);
    }

    // Close the file
    fclose(file);

    /*ultimately where routine starts, we begin profiling*/
    clock_gettime(CLOCK_MONOTONIC, &startthreads);

    int size = count / num_threads;

    // case where count is less than n_proc
    if (size == 0)
    {
        size = 1;
        num_threads = count;
    }

    // Create threads
    pthread_t threads[num_threads];
    struct thread_args args[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        args[i].numbers = numbers;
        args[i].start = i * size;
        args[i].end = (i + 1) * size;
        args[i].func = func;

        if (i == num_threads - 1)
        {
            args[i].end = count;
        }

        pthread_create(&threads[i], NULL, compute, &args[i]);
    }

    // Join threads
    unsigned long result;
    pthread_join(threads[0], (void **)&result);
    for (int i = 1; i < num_threads; i++)
    {
        unsigned long thread_result;
        pthread_join(threads[i], (void **)&thread_result);
        result = func(result, thread_result);
    }


    // Free the array
    free(numbers);

    /* profiling ends here */
    clock_gettime(CLOCK_MONOTONIC, &endthreads);

    return result;
}

#endif
