#include "ScalarProduct.h"

std::vector<float> computeRandomVectorOperations(int N, int vecs_num) {
    std::vector<float> results(vecs_num, 0);
    std::vector<std::vector<float>> vecs;

    for (int i = 0; i < N; i++){
        vecs.push_back({0});
    }
#pragma omp parallel sections shared(results, vecs)
    {
#pragma omp section
        {
            // Random vector generation section
            for (int i = 0; i < N; i++){
                vecs[i] = createRandomVector(vecs_num * 2, (float) 0.01, 100.0);}
        }
#pragma omp section
        {
            for (int j = 0; j < N; j++){
                while (vecs[j][0] == 0) continue;
                for (int k = 0; k < vecs_num; k++)
                    results[k] += vecs[j][k] * vecs[j][k + vecs_num];
            }
        }
    }
    return results;
};