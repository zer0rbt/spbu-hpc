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
T triangularMaxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for schedule(guided) reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
        for (long int j = 0; j <= i; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        if (i < n - 1)
            min_value = std::min(min_value, 0);
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

template<typename T>
T bandMaxFromMin(std::vector<std::vector<T>> matrix, long int bandWidth) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for schedule(static) reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
        long zero = 0;
        long start = std::max(zero, i - bandWidth);
        for (long int j = start; j < std::min(start + bandWidth + 1, m); j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        max_value = std::max(max_value, std::min(min_value, 0));
    }
    return max_value;
}

//todo
template<typename T>
T toeplitzMaxFromMin(std::vector<std::vector<T>> matrix, long int bandWidth) {

    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
    T min_value = std::numeric_limits<T>::max();
#pragma omp parallel reduction(max:max_value)
#pragma omp sections
#pragma omp section
    for (long int i = 0; i < m; i++) {
        if (matrix[0][i] < min_value) {
            min_value = matrix[0][i];
        }
    }
    max_value = std::max(max_value, min_value);
#pragma omp section
    for (long int i = 0; i < m; i++) {
        if (matrix[n - 1][i] < min_value) {
            min_value = matrix[n - 1][i];
        }
    }
    max_value = std::max(max_value, min_value);

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
