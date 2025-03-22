#ifndef SPBU_HPC_MAXIMIN_H
#define SPBU_HPC_MAXIMIN_H


#include <vector>
#include <limits>
#include <tuple>
#include <omp.h>

#include "vectorMin.h"



template<typename T>
T maxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
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
T triangularGuidedMaxFromMin(std::vector<std::vector<T>> matrix) {
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
            min_value = std::min(min_value, (T)0);
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

template<typename T>
T triangularStaticMaxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for schedule(static) reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
        for (long int j = 0; j <= i; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        if (i < n - 1)
            min_value = std::min(min_value, (T)0);
        max_value = std::max(max_value, min_value);
    }
    return max_value;
}

template<typename T>
T triangularDynamicMaxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();
    T max_value = std::numeric_limits<T>::min();
#pragma omp parallel for schedule(dynamic) reduction(max:max_value)
    for (long int i = 0; i < n; i++) {
        T min_value = std::numeric_limits<T>::max();
        for (long int j = 0; j <= i; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        if (i < n - 1)
            min_value = std::min(min_value, (T)0);
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
        max_value = std::max(max_value, std::min(min_value, (T)0));
    }
    return max_value;
}

template<typename T>
T toeplitzMaxFromMin(std::vector<std::vector<T>> matrix) {
    long int n = matrix.size();
    long int m = matrix[0].size();

    T global_max = std::numeric_limits<T>::min();

#pragma omp parallel reduction(max:global_max)
    {
        T local_min = std::numeric_limits<T>::max();
        long local_min_ind = -1;

#pragma omp for
        for (long int i = 0; i < n; ++i) {
            if (local_min_ind == -1 || local_min_ind >= m) {
                std::tie(local_min, local_min_ind) = minIReduction(matrix[i]);
            } else {
                if (local_min >= matrix[i][0]) {
                    local_min = matrix[i][0];
                    local_min_ind = 0;
                    global_max = std::max(global_max, local_min);
                }
            }
            local_min_ind++;
        }
    }

    return global_max;
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
