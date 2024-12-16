#ifndef SPBU_HPC_MAXIMIN_H
#define SPBU_HPC_MAXIMIN_H


#include <vector>
#include <limits>


template<typename T>
T maxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();

    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
#pragma omp parallel for reduction(min:min_value)
        for (long int j = 0; j < m; j++) {
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
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
#pragma omp parallel for reduction(min:min_value)
        for (long int j = 0; j < m; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

#endif //SPBU_HPC_MAXIMIN_H
