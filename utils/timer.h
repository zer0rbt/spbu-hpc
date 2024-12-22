#ifndef SPBU_HPC_MEASURE_TIME_H
#define SPBU_HPC_MEASURE_TIME_H

#include <iostream>
#include <vector>
#include <chrono>

/**
 * @brief Measures the execution time of a given function on a single vector.
 *
 * This function measures the time taken for the execution of the provided function
 * on a single vector of arbitrary type and outputs the duration in seconds.
 *
 * @tparam Func The type of the function to be measured. The function should accept
 *              a reference to a `std::vector<T>` as its argument and return void.
 * @tparam T The type of elements in the vector (e.g., int, float).
 *
 * @param func The function whose execution time will be measured. It should accept
 *             a reference to a `std::vector<T>`.
 * @param vec A vector of type `T` that will be passed as an argument to the function `func`.
 *            The vector may contain any number of elements of type `T`.
 * @param func_name A string representing the name of the function being measured. This is
 *                  used to output the name along with the execution time in the console.
 *
 * @example
 * std::vector<int> data = {1, 2, 3, 4, 5};
 * printExecutionTime(exampleFunction, data, "exampleFunction");
 *
 * @note The function measures the time using `std::chrono::high_resolution_clock` and outputs
 *       the duration in seconds.
 */
template<typename Func, typename T>
void printExecutionTime(Func func, std::vector<T> &vec, const std::string &func_name) {
    auto start = std::chrono::high_resolution_clock::now();
    func(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time for " << func_name << ": " << duration.count() << " seconds" << std::endl;
}

/**
 * @brief Measures the execution time of a given function on two vectors.
 *
 * This function measures the time taken for the execution of the provided function
 * on two vectors of arbitrary type and outputs the duration in seconds.
 *
 * @tparam Func The type of the function to be measured. The function should accept
 *              two references to `std::vector<T>` as its arguments and return void.
 * @tparam T The type of elements in the vectors (e.g., int, float).
 *
 * @param func The function whose execution time will be measured. It should accept
 *             two references to `std::vector<T>`.
 * @param vec1 The first vector of type `T` that will be passed as an argument to the function `func`.
 * @param vec2 The second vector of type `T` that will be passed as an argument to the function `func`.
 * @param func_name A string representing the name of the function being measured. This is
 *                  used to output the name along with the execution time in the console.
 *
 * @example
 * std::vector<float> data1 = {1.1, 2.2, 3.3, 4.4, 5.5};
 * std::vector<float> data2 = {6.6, 7.7, 8.8, 9.9, 10.10};
 * printExecutionTime(exampleFunction, data1, data2, "exampleFunction");
 *
 * @note The function measures the time using `std::chrono::high_resolution_clock` and outputs
 *       the duration in seconds.
 */
template<typename Func, typename T>
void printExecutionTime(Func func, std::vector<T> &vec1, std::vector<T> &vec2, const std::string &func_name) {
    auto start = std::chrono::high_resolution_clock::now();
    func(vec1, vec2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time for " << func_name << ": " << duration.count() << " seconds" << std::endl;
}

#endif // SPBU_HPC_MEASURE_TIME_H
