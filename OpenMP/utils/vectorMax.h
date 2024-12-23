#ifndef SPBU_HPC_VECTORMAX_H
#define SPBU_HPC_VECTORMAX_H

#include <vector>
#include <omp.h>
#include <limits>
#include <mutex>


/**
 * @brief Function to find the maximum value in a vector using OpenMP reduction.
 *
 * This function uses the OpenMP `reduction` directive to parallelize the search for the maximum value in the vector.
 * Each thread computes a local maximum, and then all local maximums are combined to get the final result.
 *
 * @param vec A vector of integers in which the maximum value is to be found.
 * @return int The maximum value in the vector.
 */
int maxReduction(std::vector<int> &vec);

/**
 * @brief Function to find the maximum value in a vector without using OpenMP reduction.
 *
 * This function parallelizes the search for the maximum value using OpenMP threads, but without using the reduction
 * directive. Each thread computes a local maximum, and then a critical section is used to update the global maximum.
 * This approach may be less efficient than using reduction but demonstrates a different method for the same task.
 *
 * @param vec A vector of integers in which the maximum value is to be found.
 * @return int The maximum value in the vector.
 */
int maxNoReduction(std::vector<int> &vec);

/**
 * @brief Finds the maximum value in a vector sequentially (without parallelization).
 *
 * This function performs a simple sequential iteration over all elements of the vector
 * to find its maximum value. It is suitable for small vectors or cases where
 * multithreading is not required.
 *
 * @param vec A vector of integers in which to find the maximum value.
 * @return int The maximum value in the vector.
 */
int sequentialMaxReduction(std::vector<int> &vec);

/**
 * @brief Finds the maximum value in a vector using a critical section for synchronization.
 *
 * This function leverages OpenMP's `#pragma omp critical` directive to synchronize
 * access to the shared maximum value variable. Only one thread can update the
 * global maximum at a time, preventing data races.
 *
 * @param vec A vector of integers in which to find the maximum value.
 * @return int The maximum value in the vector.
 */
int maxCritical(std::vector<int> &vec);

/**
 * @brief Finds the maximum value in a vector using locks for synchronization.
 *
 * This function uses `std::mutex` to synchronize access to the shared maximum
 * value variable. Threads acquire the lock before updating the global maximum
 * and release it afterward, ensuring thread safety.
 *
 * @param vec A vector of integers in which to find the maximum value.
 * @return int The maximum value in the vector.
 */
int maxLock(std::vector<int> &vec);

/**
 * @brief Finds the maximum value in a vector using atomic operations for synchronization.
 *
 * This function uses OpenMP's `#pragma omp atomic` directive to safely update
 * the shared maximum value variable. Atomic operations ensure thread safety
 * without requiring locks or critical sections.
 *
 * @param vec A vector of integers in which to find the maximum value.
 * @return int The maximum value in the vector.
 */
int maxAtomic(std::vector<int> &vec);

#endif //SPBU_HPC_VECTORMAX_H
