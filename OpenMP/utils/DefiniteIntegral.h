#ifndef SPBU_HPC_DEFINITEINTEGRAL_H
#define SPBU_HPC_DEFINITEINTEGRAL_H

#include <omp.h>

template<typename func>
double definiteIntegral(func Func, double a, double b, int N){
    double h = (b - a) / N;
    double y = 0;

#pragma omp parallel for reduction(+: y)
    for (int i = 0; i < N; i++){
        y += Func(a + i * h);
    }

    return y * h;
}

#endif //SPBU_HPC_DEFINITEINTEGRAL_H
