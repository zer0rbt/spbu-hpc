#include "randomisedFuncs.h"

void randItersSequential(int iterations, float p1, float p2, float p3) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int j = 1;j <=iterations;++j) {
        float rand_value = dis(gen);

        if (rand_value < p1) {
            continue;
        } else if (rand_value < p1 + p2) {
            volatile long long int jj = j*j;
        } else if (rand_value < p1 + p2 + p3) {
            for (int i = 0;i < 5; ++i)dis(gen);
        }
    }
};

void randItersParallelStatic(int iterations, float p1, float p2, float p3){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);
#pragma omp parallel for schedule(static)
    for (int j = 1;j <=iterations;++j) {
        float rand_value = dis(gen);

        if (rand_value < p1) {
            continue;
        } else if (rand_value < p1 + p2) {
            volatile long long int jj = j*j;
        } else if (rand_value < p1 + p2 + p3) {
            for (int i = 0;i < 5; ++i)dis(gen);
        }
    }
};

void randItersParallelDynamic(int iterations, float p1, float p2, float p3){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);
#pragma omp parallel for schedule(dynamic)
    for (int j = 1;j <=iterations;++j) {
        float rand_value = dis(gen);

        if (rand_value < p1) {
            continue;
        } else if (rand_value < p1 + p2) {
            volatile long long int jj = j*j;
        } else if (rand_value < p1 + p2 + p3) {
            for (int i = 0;i < 5; ++i)dis(gen);
        }
    }
};

void randItersParallelGuided(int iterations, float p1, float p2, float p3){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);
#pragma omp parallel for schedule(guided)
    for (int j = 1;j <=iterations;++j) {
        float rand_value = dis(gen);

        if (rand_value < p1) {
            continue;
        } else if (rand_value < p1 + p2) {
            volatile long long int jj = j*j;
        } else if (rand_value < p1 + p2 + p3) {
            for (int i = 0;i < 5; ++i)dis(gen);
        }
    }
};