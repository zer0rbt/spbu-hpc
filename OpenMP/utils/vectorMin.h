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


/**
 * @brief Finds the minimum value and its index in the given vector using parallel reduction.
 *
 * This function performs a parallel reduction to find the minimum value in the input vector
 * and returns both the minimum value and its index. The parallelization is achieved using OpenMP,
 * which splits the work across multiple threads to speed up the search for the minimum value.
 *
 * @tparam T The type of elements in the vector. Should be a numeric type.
 * @param vec A vector of elements of type T to find the minimum value and index.
 * @return A pair containing:
 *     - The minimum value in the vector.
 *     - The index of the first occurrence of the minimum value.
 *
 * @note The function uses OpenMP to parallelize the loop for better performance on large datasets.
 *       The `min` reduction clause ensures that the minimum value is found across threads.
 */
template<typename T>
std::pair<T, T> minIReduction(std::vector<T> &vec) {
    int n = vec.size();

    int min_value = std::numeric_limits<T>::max();
    int min_index = -1;

#pragma omp parallel
    {
        int local_min = std::numeric_limits<T>::max();
        int local_index = -1;

#pragma omp for reduction(min : min_value)
        for (long i = 0; i < n; ++i) {
            if (vec[i] < min_value) {
                min_value = vec[i];
                local_index = i;
            }
        }

#pragma omp critical
        {
            if (local_min == min_value) {
                min_index = local_index;
            }
        }
    }

    return {min_value, min_index};
}


#endif //SPBU_HPC_VECTORMIN_H
