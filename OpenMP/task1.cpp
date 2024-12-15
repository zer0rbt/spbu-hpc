#include "task1.h"

void task1() {
    std::vector<int> arr;
    if (!file2vec("../OpenMP/src/t1_data.txt", arr)) {
        std::cout << "Error in task 1" << std::endl;
        return;
    }

    std::cout << "File length = " << arr.size() << std::endl;
    std::cout << "Max vale (with reduction): " << maxReduction(arr) << std::endl;
    std::cout << "Max value (without reduction): " << maxNoReduction(arr) << std::endl;
    measureExecutionTime(maxReduction, arr, "maxReduction (with reduction)");
    measureExecutionTime(maxNoReduction, arr, "maxNoReduction (without reduction)");

    std::cout << "Min value (with reduction): " << minReduction(arr) << std::endl;
    std::cout << "Min value (without reduction): " << minNoReduction(arr) << std::endl;
    measureExecutionTime(minReduction, arr, "minReduction (with reduction)");
    measureExecutionTime(minNoReduction, arr, "minNoReduction (without reduction)");
}