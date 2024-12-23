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
        if (local_max > max_value) {
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

int sequentialMaxReduction(std::vector<int> &vec) {
    int n = vec.size();

    int max_value = std::numeric_limits<int>::min();
    for (int i = 0; i < n; ++i) {
        if (vec[i] > max_value) {
            max_value = vec[i];
        }
    }
    return max_value;
}

int maxAtomic(std::vector<int> &vec) {
    int n = vec.size();
    int max_value = std::numeric_limits<int>::min();

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
#pragma omp atomic
        if (vec[i] > max_value) {
            max_value = vec[i];
        }
    }
    return max_value;
}

int maxCritical(std::vector<int> &vec) {
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

#pragma omp critical
        {
            if (local_max > max_value) {
                max_value = local_max;
            }
        }
    }

    return max_value;
}

int maxLock(std::vector<int> &vec) {
    int n = vec.size();
    int max_value = std::numeric_limits<int>::min();
    std::mutex max_value_mutex;

#pragma omp parallel
    {
        int local_max = std::numeric_limits<int>::min();
#pragma omp for
        for (int i = 0; i < n; ++i) {
            if (vec[i] > local_max) {
                local_max = vec[i];
            }
        }

        max_value_mutex.lock();
        if (local_max > max_value) {
            max_value = local_max;
        }
        max_value_mutex.unlock();
    }

    return max_value;
}