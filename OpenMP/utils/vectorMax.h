#ifndef SPBU_HPC_VECTORMAX_H
#define SPBU_HPC_VECTORMAX_H

#include <vector>

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

#endif //SPBU_HPC_VECTORMAX_H
