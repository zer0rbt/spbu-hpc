#ifndef MEASURE_TIME_H
#define MEASURE_TIME_H

#include <iostream>
#include <vector>
#include <chrono>

/**
 * @brief Measures the execution time of a given function.
 *
 * This function measures the time taken for the execution of the provided function
 * on a vector of integers and outputs the duration in seconds.
 *
 * @tparam Func The type of the function to be measured. The function should accept
 *              a reference to a std::vector<int> as its argument and return void.
 *
 * @param func The function whose execution time will be measured. It should accept
 *             a reference to a std::vector<int> and return void.
 * @param vec A vector of integers that will be passed as an argument to the function `func`.
 *            The vector may contain any number of integers.
 * @param func_name A string representing the name of the function being measured. This is
 *                  used to output the name along with the execution time in the console.
 *
 * @example
 * std::vector<int> data = {1, 2, 3, 4, 5};
 * measureExecutionTime(exampleFunction, data, "exampleFunction");
 *
 * @note The function measures the time using `std::chrono::high_resolution_clock` and outputs
 *       the duration in seconds.
 */
template<typename Func>
void measureExecutionTime(Func func, std::vector<int> &vec, const std::string &func_name) {
    auto start = std::chrono::high_resolution_clock::now();
    func(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time for " << func_name << ": " << duration.count() << " seconds" << std::endl;
}

#endif // MEASURE_TIME_H
