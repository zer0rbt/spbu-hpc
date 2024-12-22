#include "task1.h"

void task1(const std::string& filename) {
    std::vector<int> arr;
    if (!file2vec(filename, arr)) {
        std::cout << "Error in task 1" << std::endl;
        return;
    }

    std::cout << "File length = " << arr.size() << std::endl;
    std::cout << "Max vale (with reduction): " << maxReduction(arr) << std::endl;
    std::cout << "Max value (without reduction): " << maxNoReduction(arr) << std::endl;
    printExecutionTime(maxReduction, arr, "maxReduction (with reduction)");
    printExecutionTime(maxNoReduction, arr, "maxNoReduction (without reduction)");
    printExecutionTime(sequentialMaxReduction, arr, "sequential");

    std::cout << "Min value (with reduction): " << minReduction(arr) << std::endl;
    std::cout << "Min value (without reduction): " << minNoReduction(arr) << std::endl;
    printExecutionTime(minReduction, arr, "minReduction (with reduction)");
    printExecutionTime(minNoReduction, arr, "minNoReduction (without reduction)");

}