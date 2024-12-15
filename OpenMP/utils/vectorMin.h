#ifndef SPBU_HPC_VECTORMIN_H
#define SPBU_HPC_VECTORMIN_H

#include <vector>


/**
 * @brief Function to find the minimum value in a vector using OpenMP reduction.
 *
 * This function uses the OpenMP `reduction` directive to parallelize the search for the minimum value in the vector.
 * Each thread computes a local minimum, and then all local minimums are combined to get the final result.
 *
 * @param vec A vector of integers in which the minimum value is to be found.
 * @return int The minimum value in the vector.
 */
int minReduction(std::vector<int> &vec);


/**
 * @brief Function to find the minimum value in a vector without using OpenMP reduction.
 *
 * This function parallelizes the search for the minimum value using OpenMP threads, but without using the reduction
 * directive. Each thread computes a local minimum, and then a critical section is used to update the global minimum.
 * This approach may be less efficient than using reduction but demonstrates a different method for the same task.
 *
 * @param vec A vector of integers in which the minimum value is to be found.
 * @return int The minimum value in the vector.
 */
int minNoReduction(std::vector<int> &vec);


#endif //SPBU_HPC_VECTORMIN_H
