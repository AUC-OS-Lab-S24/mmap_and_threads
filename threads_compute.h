#ifndef THREADS_COMPUTE_H
#define THREADS_COMPUTE_H
/*
 * Takes the number of threads, a path to a file containing numbers, a pointer to a function that takes 2 integers and returns an unsigned long integer.
 * Returns the result of applying the function on the numbers as an unsigned long integer by splitting the work as evenly as possible using multiple processes working together via shared memory.
 */
unsigned long threads_compute(int num_threads, char *file_path, unsigned long (*func)(unsigned long, unsigned long))
{
}

#endif