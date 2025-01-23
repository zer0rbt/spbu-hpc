#ifndef SPBU_HPC_TASK1_H
#define SPBU_HPC_TASK1_H

#include <vector>
#include <omp.h>
#include "../utils/fileio.h"
#include "../utils/timer.h"

#include "utils/vectorMin.h"
#include "utils/vectorMax.h"
#include "utils/randVecs.h"
/**
 * @brief Main function to perform the task of finding maximum and minimum values.
 *
 * This function reads data from a file, calculates the maximum and minimum values in the vector both
 * with and without using OpenMP reductions, and measures the execution time for each method.
 * It also prints the results to the console.
 *
 * @param filename The name of the file to read data from. This string specifies
 *                 the path to the file.
 */
void task1(const std::string& filename);

void testTask1(const std::string& filename);
#endif //SPBU_HPC_TASK1_H
