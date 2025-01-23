#ifndef SPBU_HPC_TESTER_H
#define SPBU_HPC_TESTER_H

#include <functional>
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
template <typename T, typename T_ARG>
void processFilesAndSaveResults(std::function<T(const std::vector<T_ARG>&)> func,std::vector<std::string>& inFilenames, std::string& outFilename)
{
    long int numFiles = inFilenames.size();
    std::vector<std::vector<int>> results;

    for (int i = 0; i < numFiles; ++i) {
        std::vector<T_ARG> arg;
        if (!file2vec(inFilenames[i], arg)){
            break;
        };

        T funcResult = func(arg);

        results.push_back({funcResult, static_cast<int>(arg.size())});
    }

    vec2file(results, outFilename);
}

#endif //SPBU_HPC_TESTER_H
