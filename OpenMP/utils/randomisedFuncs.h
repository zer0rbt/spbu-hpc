#ifndef SPBU_HPC_RANDOMISEDFUNCS_H
#define SPBU_HPC_RANDOMISEDFUNCS_H

#include <iostream>
#include <random>
#include <cmath>

void randItersSequential(int iterations, float p1, float p2, float p3);

void randItersParallelStatic(int iterations, float p1, float p2, float p3);

void randItersParallelDynamic(int iterations, float p1, float p2, float p3);

void randItersParallelGuided(int iterations, float p1, float p2, float p3);


#endif //SPBU_HPC_RANDOMISEDFUNCS_H
