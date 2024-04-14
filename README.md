# mmap_and_threads

## Part 1
mmap_compute:
Takes the number of processes, a path to a file containing numbers, a pointer to a function that takes 2 integers and returns an unsigned long integer.
Returns the result of applying the function on the numbers as an unsigned long integer by splitting the work as evenly as possible using multiple processes working together via shared memory.

threads_compute: Same as mmap_compute but instead of taking the number of processes, it instead takes the number of threads

Now we have:
mmap_compute
threads_compute
pipes_compute [(parallel_compute from previous project)](https://github.com/AUC-OS-Lab-S24/SequentialVsParallel)
sequential_compute [(from previous project)](https://github.com/AUC-OS-Lab-S24/SequentialVsParallel)

## Part 2
- [ ] If we fix n_proc and n_thread to the same value, then which of the 4 functions take the least time? At which value of N does this behavior persist?
- [ ] If we fix N to a large number, then which of the 4 functions take the least time? At which value of n_proc (n_thread) does this behavior persist?
- [ ] Produce 2 graphs to answer the 2 questions

## [Slides](https://docs.google.com/presentation/d/1Wg4XmHcrndz6813wmHoO_zncmwknOuQLCzqJ2ZvWM0U/edit?usp=sharing)
- [ ] Roles of every team member.
- [X] Detailed description of the inputs and outputs of mmap().
- [ ] Descriptions and pseudo-code of the 4 compute functions.
- [ ] Simple examples showing the 4 compute functions producing correct results.
- [ ] In pipes_compute and threads_compute, design figures illustrating the processes/threads and the pipes as well as the direction of flow of data.
- [ ] How the 2 tests are designed (e.g., ranges chosen).
- [ ] How and why n_proc (and n_thread) was set.
- [ ] Method of curve smoothing.
- [ ] Comparison results and answers to the 2 questions.
