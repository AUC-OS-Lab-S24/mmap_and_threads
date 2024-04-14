#ifndef MMAP_COMPUTE_H
#define MMAP_COMPUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
/*
 * Takes the number of processes, a path to a file containing numbers, a pointer to a function that takes 2 integers and returns an unsigned long integer.
 * Returns the result of applying the function on the numbers as an unsigned long integer by splitting the work as evenly as possible using multiple processes working together via shared memory.
 */
unsigned long mmap_compute(int num_processes, char *path, unsigned long (*func)(int, int))
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

    int size = count / num_processes;

    // case where count is less than n_proc
    if (size == 0)
    {
        size = 1;
        num_processes = count;
    }

    // Create a shared memory object
    unsigned long *shared_memory = (unsigned long *)mmap(NULL, num_processes * sizeof(unsigned long), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_memory == MAP_FAILED)
    {
        printf("Error creating shared memory!\n");
        return 1;
    }

    for (int i = 0; i < num_processes; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            // child process
            int start = i * size;
            // last index for last process is count - 1
            int end = (i == (num_processes - 1)) ? count : (start + size);
            unsigned long result = numbers[start];
            for (int j = start + 1; j < end; j++)
            {
                result = func(result, numbers[j]);
            }

            // write result to shared memory
            shared_memory[i] = result;
            // exit child process
            exit(0);
        }
        else
        {
            // parent process
            if (pid == -1)
            {
                printf("Error forking process!\n");
                return 1;
            }
        }
    }

    // wait for all child processes to finish
    while (1)
    {
        pid_t child = wait(NULL);
        if (child == -1)
        {
            break;
        }
    }

    // calculate final result
    unsigned long final_result = shared_memory[0];
    for (int i = 1; i < num_processes; i++)
    {
        final_result = func(final_result, shared_memory[i]);
    }

    // free memory
    free(numbers);
    munmap(shared_memory, num_processes * sizeof(unsigned long));

    return final_result;
}

#endif