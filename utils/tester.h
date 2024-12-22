#ifndef SPBU_HPC_TESTER_H
#define SPBU_HPC_TESTER_H

#include "fileio.h"
/**
 * @brief Processes files and stores the result of a function applied to each file's content.
 *
 * This function reads the content of the i-th file, applies a function `func` to the data,
 * and stores the result of the function along with the size of the input data.
 * It then stores these results in a vector of vectors.
 *
 * @tparam T The type of the elements in the vector.
 * @param func A function to be applied to the data from each file.
 * @param numFiles The number of files to process.
 * @param filename The name of the file where results will be saved.
 */
template <typename T>
void processFilesAndSaveResults(
        std::function<T(const std::vector<int>&)> func,
        int numFiles,
        const std::string& filename)
{
    std::vector<std::vector<int>> results;

    for (int i = 0; i < numFiles; ++i) {
        std::vector<int> arg = readFile(i);

        T funcResult = func(arg);

        results.push_back({funcResult, static_cast<int>(arg.size())});
    }

    writeToFile(results, filename);
}

#endif //SPBU_HPC_TESTER_H
