#include <vector>
#include <omp.h>
#include <limits>

#include "vectorMax.h"

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