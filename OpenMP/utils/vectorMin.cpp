#include <vector>
#include <omp.h>
#include <limits>
#include "vectorMin.h"


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


