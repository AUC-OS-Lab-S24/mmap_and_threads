#ifndef THREADS_COMPUTE_H
#define THREADS_COMPUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

unsigned long threads_compute(int num_threads, char *file_path, unsigned long (*func)(unsigned long, unsigned long))
{
}

#endif