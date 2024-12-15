#include <iostream>
#include <vector>
#include <omp.h>
#include <limits>
#include "../utils/fileio.h"
#include "../utils/timer.h"


int maxReduction(std::vector<int> &vec) {
    int n = vec.size();

    int max_value = std::numeric_limits<int>::min();
#pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; ++i) {
        if (vec[i] > max_value) {
            max_value = vec[i];
        }
    }
    return max_value;
}

int minReduction(std::vector<int> &vec) {
    int n = vec.size();

    int min_value = std::numeric_limits<int>::max();
#pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; ++i) {
        if (vec[i] < min_value) {
            min_value = vec[i];
        }
    }
    return min_value;
}

int maxNoReduction(std::vector<int> &vec) {
    int n = vec.size();

    int max_value = std::numeric_limits<int>::min();
#pragma omp parallel
    {
        int local_max = std::numeric_limits<int>::min();
#pragma omp for
        for (int i = 0; i < n; ++i) {
            if (vec[i] > local_max) {
                local_max = vec[i];
            }
        }
        if (local_max > max_value) { // "If" statement before "critical" to speed up the process!
#pragma omp critical
            {
                if (local_max > max_value) {
                    max_value = local_max;
                }
            }
        }
    }
    return max_value;
}

int minNoReduction(std::vector<int> &vec) {
    int n = vec.size();

    int min_value = std::numeric_limits<int>::max();
#pragma omp parallel
    {
        int local_min = std::numeric_limits<int>::max();
#pragma omp for
        for (int i = 0; i < n; ++i) {
            if (vec[i] < local_min) {
                local_min = vec[i];
            }
        }
#pragma omp critical
        {
            if (local_min < min_value) {
                min_value = local_min;
            }
        }
    }
    return min_value;
}

int main() {
    // Инициализация вектора
    std::vector<int> arr;
    if (!file2vec("../OpenMP/src/t1_data.txt", arr))
        return 0;

    std::cout << "File length = " << arr.size() << std::endl;
    std::cout << "Max vale (with reduction): " << maxReduction(arr) << std::endl;
    std::cout << "Max value (without reduction): " << maxNoReduction(arr) << std::endl;
    measureExecutionTime(maxReduction, arr, "maxReduction (with reduction)");
    measureExecutionTime(maxNoReduction, arr, "maxNoReduction (without reduction)");

    std::cout << "Min value (with reduction): " << minReduction(arr) << std::endl;
    std::cout << "Min value (without reduction): " << minNoReduction(arr) << std::endl;
    measureExecutionTime(minReduction, arr, "minReduction (with reduction)");
    measureExecutionTime(minNoReduction, arr, "minNoReduction (without reduction)");

    return 0;
}
