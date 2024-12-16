#ifndef SPBU_HPC_MAXIMIN_H
#define SPBU_HPC_MAXIMIN_H


#include <vector>
#include <limits>


template<typename T>
T maxFromMin(std::vector<std::vector<T>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int max_value = std::numeric_limits<int>::min();

    for (int i = 0; i < n; i++) {
        int min_value = std::numeric_limits<int>::max();
#pragma omp parallel for reduction(min:min_value)
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

template<typename T>
T highlyParallelMaxFromMin(std::vector<std::vector<T>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int max_value = std::numeric_limits<int>::min();
#pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < n; i++) {
        int min_value = std::numeric_limits<int>::max();
#pragma omp parallel for reduction(min:min_value)
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

#endif //SPBU_HPC_MAXIMIN_H
